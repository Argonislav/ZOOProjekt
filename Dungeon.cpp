//
// Created by matla on 5/15/2024.
//

#include "Dungeon.h"

Dungeon::Dungeon(int width, int height) : m_width(width), m_height(height), roomCount(0) {
    srand(time(0));
    generateRoom();
}
void Dungeon::generateRoom() {
    layout.resize(m_height);
    for (int y = 0; y < m_height; ++y) {
        layout[y].resize(m_width);

        for (int x = 0; x < m_width; ++x) {
            if (x == 0 || x == m_width - 1 || y == 0 || y == m_height - 1) {
                layout[y][x] = {TileType::WALL};
            } else {
                layout[y][x] = {TileType::EMPTY};
            }
        }
    }

    for (auto& row : layout) {
        for (auto& tile : row) {
            if (tile.type == TileType::PLAYER) {
                tile.type = TileType::EMPTY;
            }
        }
    }

    int exitSide = rand() % 2;
    int exitY = rand() % (m_height - 2) + 1;
    layout[exitY][exitSide * (m_width - 1)].type = TileType::DOOR;

    do {
        playerX = rand() % (m_width - 2) + 1;
        playerY = rand() % (m_height - 2) + 1;
    } while (layout[playerY][playerX].type != TileType::EMPTY);
    layout[playerY][playerX].type = TileType::PLAYER;

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

    if (newX >= 0 && newX < m_width && newY >= 0 && newY < m_height && layout[newY][newX].type != TileType::WALL && layout[newY][newX].type != TileType::OBSTACLE) {
        layout[playerY][playerX].type = TileType::EMPTY;
        playerX = newX;
        playerY = newY;
        layout[playerY][playerX].type = TileType::PLAYER;

        if (playerX == 0 || playerX == m_width - 1) {
            layout[playerY][playerX].type = TileType::WALL;
            roomCount++;
            if (roomCount >= 3) { // Podmínka ukončení hry - v plne verzi muze byt vyssi
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
                }
            }
        }
        std::cout << std::endl;
    }
}