// dungeon.cpp
#include "Dungeon.h"
#include "Sword.h"
#include "Armor.h"
#include "Potion.h"
#include "Inventory.h"
#include <iostream>

Dungeon::Dungeon(int width, int height, Hero* hero, Monster* monster)
        : m_width(width), m_height(height), roomCount(0), hero(hero), monster(monster) {
    srand(time(0));
    generateRoom();
}

void Dungeon::generateRoom() {
    // Clear the previous layout
    layout.clear();
    layout.resize(m_height, std::vector<Tile>(m_width, {TileType::WALL, nullptr, nullptr}));

    // Create empty space for the room
    for (int y = 1; y < m_height - 1; ++y) {
        for (int x = 1; x < m_width - 1; ++x) {
            layout[y][x].type = TileType::EMPTY;
        }
    }

    // Place the exit door
    if (roomCount > 0) {
        int exitSide = playerX == 0 ? m_width - 1 : 0;
        layout[playerY][exitSide].type = TileType::DOOR;
    } else {
        // Place the initial door randomly for the first room
        int exitSide = rand() % 2;
        int exitY = rand() % (m_height - 2) + 1;
        layout[exitY][exitSide * (m_width - 1)].type = TileType::DOOR;
    }

    // Place the player (ensuring it's not on a door)
    do {
        playerX = rand() % (m_width - 2) + 1;
        playerY = rand() % (m_height - 2) + 1;
    } while (layout[playerY][playerX].type != TileType::EMPTY);
    layout[playerY][playerX].type = TileType::PLAYER;

    // Place obstacles (avoiding doors and player)
    int numObstacles = (m_width * m_height) / 15;
    for (int i = 0; i < numObstacles; ++i) {
        int obstacleX, obstacleY;
        do {
            obstacleX = rand() % (m_width - 2) + 1;
            obstacleY = rand() % (m_height - 2) + 1;
        } while (layout[obstacleY][obstacleX].type != TileType::EMPTY);
        layout[obstacleY][obstacleX].type = TileType::OBSTACLE;
    }

    // Place items (one of each type, avoiding other objects)
    bool itemPlaced[3] = {false}; // Track if each item type has been placed
    int numItems = rand() % 3 + 1; // Place 1-3 items
    for (int i = 0; i < numItems; ++i) {
        int itemX, itemY, itemType;
        do {
            itemX = rand() % (m_width - 2) + 1;
            itemY = rand() % (m_height - 2) + 1;
            itemType = rand() % 3; // 0: Sword, 1: Armor, 2: Potion
        } while (layout[itemY][itemX].type != TileType::EMPTY || itemPlaced[itemType]);

        itemPlaced[itemType] = true;
        switch (itemType) {
            case 0: layout[itemY][itemX].item = new Sword("Rusty Sword", "An old, worn sword.", 5); break;
            case 1: layout[itemY][itemX].item = new Armor("Leather Armor", "Basic protection.", 2); break;
            case 2: layout[itemY][itemX].item = new Potion("Healing Potion", "Restores some health."); break;
        }
        layout[itemY][itemX].type = TileType::ITEM;
    }

    // Place the monster (avoiding other objects)
    int monsterX, monsterY;
    do {
        monsterX = rand() % (m_width - 2) + 1;
        monsterY = rand() % (m_height - 2) + 1;
    } while (layout[monsterY][monsterX].type != TileType::EMPTY);

    delete monster; // Delete the previous monster if it exists
    monster = new Monster("Goblin", 80.0f, 30.0f, 10.0f);
    layout[monsterY][monsterX].monster = monster;
    layout[monsterY][monsterX].type = TileType::MONSTER;
}

bool Dungeon::movePlayer(char direction) {
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

    // Opravená kontrola kolize
    if (newX >= 0 && newX < m_width && newY >= 0 && newY < m_height &&
        layout[newY][newX].type != TileType::WALL && layout[newY][newX].type != TileType::OBSTACLE) {

        if (layout[newY][newX].type == TileType::DOOR) {
            // Kontrola, zda je monstrum poraženo
            bool monsterAlive = false;
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    if (layout[y][x].type == TileType::MONSTER) {
                        monsterAlive = true;
                        break;
                    }
                }
            }

            if (monsterAlive) {
                std::cout << "You must defeat the monster in this room before you can proceed!" << std::endl;

                // Vrácení hráče na předchozí pozici
                layout[newY][newX].type = TileType::DOOR; // Obnovíme dlaždici dveří
                layout[playerY][playerX].type = TileType::PLAYER; // Vrátíme hráče zpět

                return false; // Zůstaneme ve stejné místnosti
            } else {
                // Přejdeme do další místnosti
                roomCount++;
                if (roomCount >= 3) {
                    std::cout << "Congratulations! You have successfully completed the dungeon!" << std::endl;
                    return true;
                }
                std::cout << "Entering the next room!" << std::endl;
                generateRoom();

                // Nastavení pozice hráče na pozici dveří v nové místnosti
                if (playerX == 0) {
                    playerX = m_width - 1; // Hráč přišel zleva, dveře jsou vpravo
                } else {
                    playerX = 0; // Hráč přišel zprava, dveře jsou vlevo
                }
            }
        } else if (layout[newY][newX].type == TileType::ITEM) {
            Item* foundItem = layout[newY][newX].item;
            if (hero->getInventory()->addItem(foundItem)) {
                std::cout << "You found a " << foundItem->getName() << "! " << foundItem->getDescription() << std::endl;
                std::cout << "It has been added to your inventory." << std::endl;
                layout[newY][newX].item = nullptr; // Remove item from the dungeon
            } else {
                std::cout << "You found a " << foundItem->getName() << "! " << foundItem->getDescription() << std::endl;
                std::cout << "Your inventory is full. You cannot pick it up." << std::endl;
            }

            // Nastavení pozice hráče na pozici předmětu
            layout[playerY][playerX].type = TileType::EMPTY;
            playerX = newX;
            playerY = newY;
            layout[playerY][playerX].type = TileType::PLAYER;
        } else if (layout[newY][newX].type == TileType::MONSTER) {
            // Setkání s monstrem - nabídka možností
            monster = static_cast<Monster*>(layout[newY][newX].monster);
            std::cout << "You encountered a " << monster->getName() << "!" << std::endl;
            std::cout << "Monster Stats:" << std::endl;
            std::cout << "  Health: " << monster->getHealth() << std::endl;
            std::cout << "  Attack: " << monster->getAttack() << std::endl;
            std::cout << "  Defense: " << monster->getDefense() << std::endl;

            char choice;
            do {
                std::cout << "\nWhat do you want to do? (f)ight or (r)un: ";
                std::cin >> choice;
            } while (choice != 'f' && choice != 'r');

            if (choice == 'f') {
                // Boj s monstrem
                std::cout << "Prepare for battle!" << std::endl;
                while (hero->isAlive() && monster->isAlive()) {
                    // Hero attacks first
                    hero->attack(monster);
                    // Check if the monster is defeated
                    if (!monster->isAlive()) {
                        std::cout << "You defeated the monster!" << std::endl;
                        layout[newY][newX].type = TileType::EMPTY;
                        break;
                    }
                    // Monster attacks
                    monster->attack(hero);
                    // Check if the hero is defeated
                    if (!hero->isAlive()) {
                        std::cout << "You were defeated by the monster!" << std::endl;
                        return true; // Game over
                    }
                }
            } else if (choice == 'r') {
                // Útěk - hráč se vrací na předchozí pozici
                std::cout << "You run away!" << std::endl;
                layout[newY][newX].type = TileType::MONSTER; // Obnovíme dlaždici monstra
                layout[playerY][playerX].type = TileType::PLAYER; // Vrátíme hráče na původní pozici
                return false; // Nepokračujeme v pohybu
            }
        } else {
            // Ostatní pohyby - hráč se posune na nové místo
            layout[playerY][playerX].type = TileType::EMPTY;
            playerX = newX;
            playerY = newY;
            layout[playerY][playerX].type = TileType::PLAYER;
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
                std::cout << 'P'; // Player
            } else {
                switch (layout[y][x].type) {
                    case TileType::EMPTY: std::cout << '.'; break; // Empty space
                    case TileType::WALL: std::cout << '#'; break; // Wall
                    case TileType::DOOR: std::cout << 'D'; break; // Door
                    case TileType::OBSTACLE: std::cout << 'O'; break; // Obstacle
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
                    case TileType::MONSTER: std::cout << 'M'; break; // Monster
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
    if (layout[playerY][playerX].type == TileType::ITEM) {
        layout[playerY][playerX].item = nullptr;
        layout[playerY][playerX].type = TileType::EMPTY;
    }
}

Item* Dungeon::getPlayerItem() {
    if (layout[playerY][playerX].type == TileType::ITEM) {
        return layout[playerY][playerX].item;
    }
    return nullptr;
}

TileType Dungeon::getPlayerTileType() const {
    return layout[playerY][playerX].type;
}