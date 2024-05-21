#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Item.h"  // Include your Item header
#include "Inventory.h"

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

public:
    Dungeon(int width, int height);
    void generateRoom();
    bool movePlayer(char direction, Inventory& inventory);
    void print() const;
    bool playerOnItem();
    void removePlayerItem();
    Item* getPlayerItem();
};

#endif // ZOOPROJEKT_DUNGEON_H