//
// Created by Lukas Houska on 12.05.2024.
//

#ifndef ZOOPROJEKT_GAME_H
#define ZOOPROJEKT_GAME_H
#include "Dungeon.h"


class Game {
public:
    Game();
    void run();

private:
    void showMenu() const;
    void startNewGame();
    void endGame() const;
};


#endif //ZOOPROJEKT_GAME_H
