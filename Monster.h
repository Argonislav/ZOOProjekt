//
// Created by Jindřich Šantrůček on 12.05.2024.
//

#ifndef UNTITLED_MONSTER_H
#define UNTITLED_MONSTER_H

#include "Character.h"
#include "Game.h"

class Monster: public Character {
private:
    Difficulty difficulty; // Ensure Difficulty is accessible here
public:
    Monster(std::string name, float health, float attack, float defense, Difficulty difficulty);
    void printInfo();
};


#endif //UNTITLED_MONSTER_H
