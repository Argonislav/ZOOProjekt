// dungeon.cpp
#include "Dungeon.h"
#include "Sword.h"
#include "Armor.h"
#include "Potion.h"
#include "Inventory.h"
#include <iostream>

Dungeon::Dungeon(int width, int height, Hero* hero, Monster* monster, Difficulty difficulty)
        : m_width(width), m_height(height), roomCount(0), hero(hero), monster(monster), difficulty(difficulty) {
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

    // Place obstacles (adjust number based on difficulty)
    int numObstacles;
    if (difficulty == Difficulty::Easy) {
        numObstacles = (m_width * m_height) / 20; // Fewer obstacles
    } else if (difficulty == Difficulty::Medium) {
        numObstacles = (m_width * m_height) / 15;
    } else {
        numObstacles = (m_width * m_height) / 10; // More obstacles
    }
    for (int i = 0; i < numObstacles; ++i) {
        int obstacleX, obstacleY;
        do {
            obstacleX = rand() % (m_width - 2) + 1;
            obstacleY = rand() % (m_height - 2) + 1;
        } while (layout[obstacleY][obstacleX].type != TileType::EMPTY);
        layout[obstacleY][obstacleX].type = TileType::OBSTACLE;
    }

    // Place items (adjust number and types based on difficulty)
    bool itemPlaced[3] = {false}; // Track if each item type has been placed
    int numItems;
    if (difficulty == Difficulty::Easy) {
        numItems = rand() % 3 + 2; // Place 2-4 items
    } else if (difficulty == Difficulty::Medium) {
        numItems = rand() % 3 + 1; // Place 1-3 items
    } else {
        numItems = rand() % 2; // Place 0-1 items
    }
    for (int i = 0; i < numItems; ++i) {
        int itemX, itemY, itemType;
        do {
            itemX = rand() % (m_width - 2) + 1;
            itemY = rand() % (m_height - 2) + 1;
            itemType = rand() % 3; // 0: Sword, 1: Armor, 2: Potion
        } while (layout[itemY][itemX].type != TileType::EMPTY || itemPlaced[itemType]);

        itemPlaced[itemType] = true;
        switch (itemType) {
            case 0:
                layout[itemY][itemX].item = new Sword("Rusty Sword", "An old, worn sword.", 5, hero);
                break;
            case 1:
                layout[itemY][itemX].item = new Armor("Leather Armor", "Basic protection.", 2, hero);
                break;
            case 2: {
                // Náhodný výběr typu lektvaru
                auto potionType = static_cast<PotionType>(rand() % 3); // 0: Health, 1: Attack, 2: Defense
                std::string potionName, potionDescription;

                switch (potionType) {
                    case PotionType::Health:
                        potionName = "Healing Potion";
                        potionDescription = "Restores some health.";
                        break;
                    case PotionType::Attack:
                        potionName = "Attack Potion";
                        potionDescription = "Increases attack power.";
                        break;
                    case PotionType::Defense:
                        potionName = "Defense Potion";
                        potionDescription = "Increases defense power.";
                        break;
                }
                layout[itemY][itemX].item = new Potion(potionName, potionDescription, hero, potionType);
                break;
            }
        }
        layout[itemY][itemX].type = TileType::ITEM;
    }

    // Place the player (ensuring it's not on a door)
    do {
        playerX = rand() % (m_width - 2) + 1;
        playerY = rand() % (m_height - 2) + 1;
    } while (layout[playerY][playerX].type != TileType::EMPTY);
    layout[playerY][playerX].type = TileType::PLAYER;

    // Place the monster (avoiding other objects)
    int monsterX, monsterY;
    do {
        monsterX = rand() % (m_width - 2) + 1;
        monsterY = rand() % (m_height - 2) + 1;
    } while (layout[monsterY][monsterX].type != TileType::EMPTY);

    delete monster; // Delete the previous monster
    if (difficulty == Difficulty::Easy) {
        monster = new Monster("Weak Goblin", 50.0f, 10.0f, 5.0f, difficulty);
    } else if (difficulty == Difficulty::Medium) {
        monster = new Monster("Goblin", 80.0f, 20.0f, 10.0f, difficulty);
    } else {
        monster = new Monster("Strong Goblin", 120.0f, 30.0f, 15.0f, difficulty);
    }

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

    if (newX >= 0 && newX < m_width && newY >= 0 && newY < m_height &&
        layout[newY][newX].type != TileType::WALL && layout[newY][newX].type != TileType::OBSTACLE) {

        if (layout[newY][newX].type == TileType::DOOR) {
            if (monster != nullptr && monster->isAlive()) {
                std::cout << "You must defeat the monster in this room before you can proceed!" << std::endl;
                return false; // Stay in the same room
            } else {
                roomCount++;
                if (roomCount >= 3) {
                    std::cout << "Congratulations! You have successfully completed the dungeon!" << std::endl;
                    return true; // Indicate game has been won
                }
                std::cout << "Entering the next room!" << std::endl;
                generateRoom();

                if (playerX == 0) {
                    playerX = m_width - 1;
                } else {
                    playerX = 0;
                }
            }
        } else if (layout[newY][newX].type == TileType::ITEM) {
            Item* foundItem = layout[newY][newX].item;
            if (hero->getInventory()->addItem(foundItem)) {
                std::cout << "You found a " << foundItem->getName() << "! " << foundItem->getDescription() << std::endl;
                std::cout << "It has been added to your inventory." << std::endl;
                layout[newY][newX].item = nullptr; // Remove item from the dungeon
                foundItem->setEquipped(false);
            } else {
                std::cout << "Your inventory is full. You cannot pick it up." << std::endl;
            }

            layout[playerY][playerX].type = TileType::EMPTY;
            playerX = newX;
            playerY = newY;
            layout[playerY][playerX].type = TileType::PLAYER;
        } else if (layout[newY][newX].type == TileType::MONSTER) {
            Monster* encounteredMonster = layout[newY][newX].monster;
            std::cout << "You encountered a " << encounteredMonster->getName() << "!" << std::endl;
            std::cout << "Monster Stats:" << std::endl;
            std::cout << "  Health: " << encounteredMonster->getHealth() << std::endl;
            std::cout << "  Attack: " << encounteredMonster->getAttack() << std::endl;
            std::cout << "  Defense: " << encounteredMonster->getDefense() << std::endl;

            std::cout << "\nWhat do you want to do? (f)ight or (r)un: ";
            char choice;
            std::cin >> choice;

            if (choice == 'f') {
                std::cout << "Prepare for battle!" << std::endl;

                bool playerStarts = rand() % 2 == 0;
                bool playerTurn = playerStarts;
                defenseTurnsLeft = -1;

                while (hero->isAlive() && encounteredMonster->isAlive()) {
                    if (playerTurn) {
                        this->playerTurn(encounteredMonster);

                        // Check if the player defended, and if so, let the monster attack twice
                        while (defenseTurnsLeft > 0) {
                            if (encounteredMonster->isAlive()) {
                                monsterTurn(encounteredMonster);
                                defenseTurnsLeft--;
                            }
                        }
                        if (defenseTurnsLeft == 0) {
                            hero->removeDefenseBonus(10); // Remove defense bonus after two turns
                            defenseTurnsLeft = -1;
                        }
                    } else {
                        monsterTurn(encounteredMonster);
                    }
                    playerTurn = !playerTurn; // Switch turns
                }

                if (!encounteredMonster->isAlive()) {
                    std::cout << "You defeated the monster!" << std::endl;
                    layout[newY][newX].type = TileType::EMPTY;
                    layout[newY][newX].monster = nullptr;
                } else {
                    std::cout << "You were defeated by the monster!" << std::endl;
                    gameOver = true; // Set gameOver to true
                    return false; // Do not end the game here
                }
            } else if (choice == 'r') {
                std::cout << "You run away!" << std::endl;
                return false; // Do not continue moving
            }
        } else {
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

void Dungeon::playerTurn(Monster* monster) {
    std::cout << "Your turn!\n";
    std::cout << "Choose action: (a)ttack, (d)efend, (h)eavy attack: ";
    char choice;
    std::cin >> choice;

    switch (choice) {
        case 'a':
            hero->attack(monster);
            break;
        case 'd':
            defenseTurnsLeft = 2; // Enable defense for one turn
            hero->addDefenseBonus(10); // Add defense bonus immediately
            std::cout << "You raise your defense!\n";

            std::cout << "\nYour hero's stats:\n";
            std::cout << "Health: " << hero->getHealth() << std::endl;
            std::cout << "Attack: " << hero->getAttack() << std::endl;
            std::cout << "Defense: " << hero->getDefense() << std::endl;
            break;
        case 'h':
            if (defenseTurnsLeft > 0) {
                std::cout << "You cannot use heavy attack while defending!\n";
            } else {
                float heavyAttackDamage = hero->getAttack() * 1.5f;
                std::cout << "You used a heavy attack for " << heavyAttackDamage << " damage!\n";
                monster->takeDamage(heavyAttackDamage);
            }
            break;
        default:
            std::cout << "Invalid choice!\n";
    }
    }

void Dungeon::monsterTurn(Monster* monster) {
    std::cout << "Monster's turn!\n";
    monster->attack(hero);
}

void Dungeon::print() const {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            if (x == playerX && y == playerY) {
                std::cout << 'H'; // Player
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
                                std::cout << 'P'; //  Potion
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