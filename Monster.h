//
// Created by Jindřich Šantrůček on 12.05.2024.
//

#ifndef UNTITLED_MONSTER_H
#define UNTITLED_MONSTER_H

#include "Character.h"


class Monster: public Character {
public:
    Monster( std::string name, float health, float attack, float defense);
    void printInfo();

};


#endif //UNTITLED_MONSTER_H
