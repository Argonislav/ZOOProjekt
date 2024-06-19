#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Monster.h"

enum class TileType { EMPTY, WALL, DOOR, PLAYER, MONSTER, OBSTACLE, ITEM }; // Add MONSTER tile type

struct Tile {
    TileType type;
    Item* item; // Pointer to an item (can be nullptr if no item)
    Monster* monster; // Pointer to a monster (can be nullptr if no monster)
};

class Dungeon {
private:
    std::vector<std::vector<Tile>> layout;
    int playerX, playerY;
    int m_height, m_width;
    int roomCount;
    Hero* hero; // Reference to the Hero
    Monster* monster; // Pointer to the monster
    Difficulty difficulty;

public:
    Dungeon(int width, int height, Hero* hero, Monster* monster, Difficulty difficulty);
    void generateRoom();
    bool movePlayer(char direction);
    void print() const;
    bool playerOnItem();
    void removePlayerItem();
    Item* getPlayerItem();
    TileType getPlayerTileType() const; // Add method declaration
};

#endif // ZOOPROJEKT_DUNGEON_H