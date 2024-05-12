//
// Created by Jindřich Šantrůček on 12.05.2024.
//

#ifndef UNTITLED_HERO_H
#define UNTITLED_HERO_H

#include <string>
#include "Character.h"


class Hero: public Character {
public:
    Hero(std::string name, float health, float attack, float defense);

};


#endif //UNTITLED_HERO_H
