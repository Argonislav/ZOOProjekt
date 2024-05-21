#ifndef ZOOPROJEKT_GAME_H
#define ZOOPROJEKT_GAME_H
#include "Dungeon.h"
#include "Hero.h"

class Game {
private:
    Hero *hero;
public:
    Game();
    void showMenu() const;
    void startNewGame();
    void endGame() const;
    void run();
};

#endif //ZOOPROJEKT_GAME_H