#include "Game.h"
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

    // Set hero stats statically
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
    std::cout << std::endl;

    Dungeon dungeon(10, 7);
    dungeon.print();

    char direction;
    while (true) {
        std::cout << "Enter a key to move (or 'q' to quit): ";
        std::cin >> direction;
        if (direction == 'q') {
            break;
        }
        if (dungeon.movePlayer(direction)) {
            break;
        }
        std::cout << std::endl;
        dungeon.print();
    }

    delete hero;
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