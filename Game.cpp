// game.cpp
#include "Game.h"
#include "Inventory.h"
#include "Hero.h"
#include "Monster.h"
#include <iostream>

Game::Game() : hero(nullptr) {}

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

    // Display hero stats
    std::cout << "\nYour hero's stats:\n";
    std::cout << "Name: " << hero->getName() << std::endl;
    std::cout << "Health: " << hero->getHealth() << std::endl;
    std::cout << "Attack: " << hero->getAttack() << std::endl;
    std::cout << "Defense: " << hero->getDefense() << std::endl;

    Inventory inventory(10); // Create inventory with capacity of 10
    hero->setInventory(&inventory); // Associate inventory with the hero

    // Create a monster
    Monster* monster = new Monster("Goblin", 80.0f, 30.0f, 10.0f); // Adjust monster stats accordingly

    // Display monster stats
    std::cout << "\nThe enemy monster's stats:\n";
    std::cout << "Name: " << monster->getName() << std::endl;
    std::cout << "Health: " << monster->getHealth() << std::endl;
    std::cout << "Attack: " << monster->getAttack() << std::endl;
    std::cout << "Defense: " << monster->getDefense() << std::endl;

    Dungeon dungeon(10, 7, hero, monster); // Pass Hero and Monster to Dungeon
    dungeon.print();

    char action;
    while (true) {
        std::cout << "Enter a key to move (w, a, s, d), 'i' to view inventory, or 'q' to quit: ";
        std::cin >> action;

        if (action == 'q') {
            break;
        } else if (action == 'i') {
            hero->getInventory()->printItems(); // Use getter to access inventory
        } else {
            if (dungeon.movePlayer(action)) { // No need to pass inventory
                break; // Game over (player won or lost)
            }

            // Check if the player is on an item tile and pick it up
            if (dungeon.playerOnItem()) {
                Item* foundItem = dungeon.getPlayerItem();

                if (hero->getInventory()->addItem(foundItem)) {
                    std::cout << "You found a " << foundItem->getName() << "! " << foundItem->getDescription() << std::endl;
                    std::cout << "It has been added to your inventory." << std::endl;
                } else {
                    std::cout << "You found a " << foundItem->getName() << "! " << foundItem->getDescription() << std::endl;
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

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                startNewGame();
                break;
            case 2:
                endGame();
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 2);
}