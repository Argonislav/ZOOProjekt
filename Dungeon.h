// dungeon.h
#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Inventory.h"
#include "Hero.h"  // Include the Hero header

enum class TileType { EMPTY, WALL, DOOR, PLAYER, OBSTACLE, ITEM };

struct Tile {
    TileType type;
    Item* item; // Pointer to an item (can be nullptr if no item)
};

class Dungeon {
private:
    std::vector<std::vector<Tile>> layout;
    int playerX, playerY;
    int m_height, m_width;
    int roomCount;
    Hero* hero; // Reference to the Hero

public:
    Dungeon(int width, int height, Hero* hero); // Modify constructor to accept Hero
    void generateRoom();
    bool movePlayer(char direction);
    void print() const;
    bool playerOnItem();
    void removePlayerItem();
    Item* getPlayerItem();
};

#endif // ZOOPROJEKT_DUNGEON_H