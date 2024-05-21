//
// Created by Lukas Houska on 12.05.2024.
//

#include "Game.h"
Game::Game() {}

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

void Game::showMenu() const {
    std::cout << "======== Dungeon Game ========" << std::endl;
    std::cout << "1. New game" << std::endl;
    std::cout << "2. End" << std::endl;
    std::cout << "Choose option:";
}

void Game::startNewGame() {
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
}

void Game::endGame() const {
    std::cout << "Game was terminated. Goodbye! <3" << std::endl;
}
