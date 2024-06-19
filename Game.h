#ifndef ZOOPROJEKT_GAME_H
#define ZOOPROJEKT_GAME_H

#include "Hero.h"

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

class Game {
private:
    Hero *hero;
    Difficulty difficulty;
public:
    Game();
    void showMenu() const;
    void startNewGame();
    void endGame() const;
    void run();
    void setDifficulty(Difficulty diff);
};

#endif //ZOOPROJEKT_GAME_H