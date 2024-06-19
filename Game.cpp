#include "Game.h"
#include "Inventory.h"
#include "Hero.h"
#include "Monster.h"
#include "Armor.h"
#include "Sword.h"
#include "Dungeon.h"
#include <iostream>

Game::Game() : hero(nullptr), difficulty(Difficulty::Medium) {} // Default to Medium difficulty

void Game::showMenu() const {
    std::cout << "======== Dungeon Game ========" << std::endl;
    std::cout << "1. New game" << std::endl;
    std::cout << "2. End" << std::endl;
    std::cout << "Choose option:";
}

void Game::startNewGame() {
    std::string heroName;
    std::cout << "Enter your hero's name: ";
    std::cin >> heroName;

    // Set hero stats
    float health = 100.0f;
    float attack = 50.0f;
    float defense = 0.0f;

    hero = new Hero(heroName, health, attack, defense);

    Inventory inventory(10); // Create inventory with capacity of 10
    hero->setInventory(&inventory); // Associate inventory with the hero

    // Výběr obtížnosti
    int difficultyChoice;
    std::cout << "Choose difficulty:\n1. Easy\n2. Medium\n3. Hard\nYour choice: ";
    std::cin >> difficultyChoice;

    switch (difficultyChoice) {
        case 1:
            setDifficulty(Difficulty::Easy);
            break;
        case 2:
            setDifficulty(Difficulty::Medium);
            break;
        case 3:
            setDifficulty(Difficulty::Hard);
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Medium difficulty.\n";
            setDifficulty(Difficulty::Medium);
    }

    // Create a monster (pass the chosen difficulty)
    Monster* monster = new Monster("Goblin", 80.0f, 30.0f, 10.0f, difficulty); // Adjust monster stats accordingly

    Dungeon dungeon(10, 7, hero, monster, difficulty); // Pass Hero and Monster to Dungeon
    dungeon.print();

    char action;
    while (true) {
        std::cout << "Enter a key to move (w, a, s, d), 'i' to view inventory, 't' to view hero stats, or 'q' to quit: ";
        std::cin >> action;

        if (action == 'q') {
            break;
        } else if (action == 'i') {
            // Správa inventáře
            hero->getInventory()->printItems();
            char invAction;
            std::cout << "Press 'e' to equip item, 'u' to use item, or 'r' to unequip item: ";
            std::cin >> invAction;

            if (invAction == 'e' || invAction == 'u') {
                unsigned long long int itemNumber;
                std::cout << "Enter item number: ";
                std::cin >> itemNumber;

                if (itemNumber < hero->inventory->items.size()) {
                    Item* selectedItem = hero->inventory->items[itemNumber];

                    if (invAction == 'e' && selectedItem->getType() == ItemType::Equipable) {
                        selectedItem->use(); // Vybavení nebo odvybavení předmětu
                    } else if (invAction == 'u' && selectedItem->getType() == ItemType::Consumable) {
                        selectedItem->use(); // Použití spotřebního předmětu
                        hero->getInventory()->removeItem(selectedItem);
                        delete selectedItem;
                    } else {
                        std::cout << "Invalid action for this item type.\n";
                    }
                } else {
                    std::cout << "Invalid item number.\n";
                }
            } else if (invAction == 'r') {
                unsigned long long int itemNumber;
                std::cout << "Enter item number: ";
                std::cin >> itemNumber;

                if (itemNumber < hero->inventory->items.size()) {
                    Item* selectedItem = hero->inventory->items[itemNumber];

                    if (selectedItem->getType() == ItemType::Equipable && selectedItem->getEquipped()) {
                        selectedItem->use(); // Odvybavení předmětu
                    } else {
                        std::cout << "This item is not equipped or is not equipable.\n";
                    }
                } else {
                    std::cout << "Invalid item number.\n";
                }
            }
        } else if (action == 't') {
            // Display hero stats
            std::cout << "\nYour hero's stats:\n";
            std::cout << "Health: " << hero->getHealth() << std::endl;
            std::cout << "Attack: " << hero->getAttack() << std::endl;
            std::cout << "Defense: " << hero->getDefense() << std::endl;
        } else {
            if (dungeon.movePlayer(action)) {
                break; // Game over (player won or lost)
            }

            // Check if the player is on an item tile and pick it up
            if (dungeon.playerOnItem()) {
                Item* foundItem = dungeon.getPlayerItem();

                if (hero->getInventory()->addItem(foundItem)) {
                    std::cout << "You found a " << foundItem->getName() << "! " << foundItem->getDescription() << std::endl;
                    std::cout << "It has been added to your inventory." << std::endl;
                } else {
                    std::cout << "Your inventory is full. You cannot pick it up." << std::endl;
                }

                dungeon.removePlayerItem();
            }

            // Check if the player encountered a monster
            if (dungeon.getPlayerTileType() == TileType::MONSTER) {
                std::cout << "You encountered a monster: " << monster->getName() << std::endl;
                std::cout << "Prepare for battle!" << std::endl;
            }

            std::cout << std::endl;
            dungeon.print();
        }
    }

    delete hero;  // Clean up the dynamically allocated Hero object
    delete monster; // Clean up the dynamically allocated Monster object
}

void Game::endGame() const {
    std::cout << "Game was terminated. Goodbye! <3" << std::endl;
}

void Game::run() {
    int choice;
    bool playing = true; // Flag to indicate if the game is running

    while (playing) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                startNewGame();

                // Logika po skončení hry (přesunuta mimo switch)
                if (hero && !hero->isAlive()) {
                    std::cout << "You have been defeated. Game over!" << std::endl;
                }
                else if (hero && hero->isAlive()) {
                    std::cout << "Congratulations! You have won the game!" << std::endl;
                }

                char playAgain;
                std::cout << "Do you want to play again? (y/n): ";
                std::cin >> playAgain;
                if (playAgain != 'y') {
                    playing = false; // Nastavení příznaku pro ukončení smyčky
                }

                delete hero;
                hero = nullptr;
                break; // Start a new game


            case 2:
                endGame();
                playing = false; // Nastavení příznaku pro ukončení smyčky
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void Game::setDifficulty(Difficulty diff) {
    difficulty = diff;
}