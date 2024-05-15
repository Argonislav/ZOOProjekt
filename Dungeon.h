//
// Created by matla on 5/15/2024.
//

#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


enum class TileType { EMPTY, WALL, DOOR, PLAYER, OBSTACLE };


struct Tile {
    TileType type;
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
    bool movePlayer(char direction);
    void print() const;
};

#endif // ZOOPROJEKT_DUNGEON_H
