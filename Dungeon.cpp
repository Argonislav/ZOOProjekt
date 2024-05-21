#include "Dungeon.h"
#include "Sword.h"
#include "Armor.h"
#include "Potion.h"
#include "Inventory.h"

#include <iostream>

Dungeon::Dungeon(int width, int height) : m_width(width), m_height(height), roomCount(0) {
    srand(time(0));
    generateRoom();
}

void Dungeon::generateRoom() {
    // Clear the previous layout
    layout.clear();
    layout.resize(m_height);
    for (int y = 0; y < m_height; ++y) {
        layout[y].resize(m_width);
        for (int x = 0; x < m_width; ++x) {
            layout[y][x] = {TileType::WALL, nullptr};
        }
    }

    // Create empty space for the room
    for (int y = 1; y < m_height - 1; ++y) {
        for (int x = 1; x < m_width - 1; ++x) {
            layout[y][x].type = TileType::EMPTY;
        }
    }

    // Place the exit door
    int exitSide = rand() % 2;
    int exitY = rand() % (m_height - 2) + 1;
    layout[exitY][exitSide * (m_width - 1)].type = TileType::DOOR;

    // Place the player
    do {
        playerX = rand() % (m_width - 2) + 1;
        playerY = rand() % (m_height - 2) + 1;
    } while (layout[playerY][playerX].type != TileType::EMPTY);
    layout[playerY][playerX].type = TileType::PLAYER;

    // Place obstacles
    int numObstacles = (m_width * m_height) / 15;
    int obstacleDistanceFromDoor = 2;
    for (int i = 0; i < numObstacles; ++i) {
        int obstacleX, obstacleY;
        do {
            obstacleX = rand() % (m_width - 2) + 1;
            obstacleY = rand() % (m_height - 2) + 1;
        } while (layout[obstacleY][obstacleX].type != TileType::EMPTY ||
                 (abs(obstacleX - exitSide * (m_width - 1)) <= obstacleDistanceFromDoor &&
                  abs(obstacleY - exitY) <= obstacleDistanceFromDoor));
        layout[obstacleY][obstacleX].type = TileType::OBSTACLE;
    }

    // Add items to the room (only one of each type)
    bool itemPlaced[3] = {false, false, false}; // 0: Sword, 1: Armor, 2: Potion
    int numItems = rand() % 3 + 1; // Randomly place 1-3 items per room
    for (int i = 0; i < numItems; ++i) {
        int itemX, itemY;
        do {
            itemX = rand() % (m_width - 2) + 1;
            itemY = rand() % (m_height - 2) + 1;
        } while (layout[itemY][itemX].type != TileType::EMPTY);

        // Determine item type randomly, ensuring only one of each type is placed
        int itemType;
        do {
            itemType = rand() % 3;
        } while (itemPlaced[itemType]);

        itemPlaced[itemType] = true;

        switch (itemType) {
            case 0:
                layout[itemY][itemX].item = new Sword("Rusty Sword", "An old, worn sword.", 5);
                break;
            case 1:
                layout[itemY][itemX].item = new Armor("Leather Armor", "Basic protection.", 2);
                break;
            case 2:
                layout[itemY][itemX].item = new Potion("Healing Potion", "Restores some health.");
                break;
        }
        layout[itemY][itemX].type = TileType::ITEM;
    }
}

bool Dungeon::movePlayer(char direction, Inventory& inventory) {
    int dx = 0, dy = 0;
    switch (direction) {
        case 'w': dy = -1; break;
        case 'a': dx = -1; break;
        case 's': dy = 1; break;
        case 'd': dx = 1; break;
        default:
            std::cout << "Invalid input! Use w, a, s, or d for movement." << std::endl;
            return false;
    }

    int newX = playerX + dx;
    int newY = playerY + dy;

    if (newX >= 0 && newX < m_width && newY >= 0 && newY < m_height &&
        layout[newY][newX].type != TileType::WALL && layout[newY][newX].type != TileType::OBSTACLE) {

        layout[playerY][playerX].type = TileType::EMPTY;
        playerX = newX;
        playerY = newY;
        layout[playerY][playerX].type = TileType::PLAYER;

        if (layout[newY][newX].type == TileType::ITEM) {
            Item* foundItem = layout[newY][newX].item;

            if (inventory.addItem(foundItem)) {
                std::cout << "You found a " << foundItem->getName() << "! " << foundItem->getDescription() << std::endl;
                std::cout << "It has been added to your inventory." << std::endl;
            } else {
                std::cout << "You found a " << foundItem->getName() << "! " << foundItem->getDescription() << std::endl;
                std::cout << "Your inventory is full. You cannot pick it up." << std::endl;
            }
        }

        if (playerX == 0 || playerX == m_width - 1) {
            layout[playerY][playerX].type = TileType::WALL;
            roomCount++;
            if (roomCount >= 3) {
                std::cout << "Congratulations! You have successfully completed the dungeon!" << std::endl;
                return true;
            }
            std::cout << "Entering the next room!" << std::endl;
            generateRoom();
        }
    } else {
        std::cout << "You can't move there!" << std::endl;
    }

    return false;
}

void Dungeon::print() const {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            if (x == playerX && y == playerY) {
                std::cout << 'P';
            } else {
                switch (layout[y][x].type) {
                    case TileType::EMPTY: std::cout << '.'; break;
                    case TileType::WALL: std::cout << '#'; break;
                    case TileType::DOOR: std::cout << 'D'; break;
                    case TileType::OBSTACLE: std::cout << 'O'; break;
                    case TileType::ITEM:
                        if (layout[y][x].item != nullptr) {
                            if (dynamic_cast<Sword*>(layout[y][x].item)) {
                                std::cout << 'S'; // Sword
                            } else if (dynamic_cast<Armor*>(layout[y][x].item)) {
                                std::cout << 'A'; // Armor
                            } else if (dynamic_cast<Potion*>(layout[y][x].item)) {
                                std::cout << 'H'; // Health Potion
                            }
                        } else {
                            std::cout << '?'; // Unknown item (shouldn't happen)
                        }
                        break;
                }
            }
        }
        std::cout << std::endl;
    }
}

bool Dungeon::playerOnItem() {
    return layout[playerY][playerX].type == TileType::ITEM;
}

void Dungeon::removePlayerItem() {
    layout[playerY][playerX].type = TileType::EMPTY;
    layout[playerY][playerX].item = nullptr;
}

Item* Dungeon::getPlayerItem() {
    return layout[playerY][playerX].item;
}