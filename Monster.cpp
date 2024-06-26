//
// Created by Jindřich Šantrůček on 12.05.2024.
//

#include <iostream>
#include "Monster.h"

Monster::Monster(std::string name, float health, float attack, float defense, Difficulty difficulty)
        : Character(name, health, attack, defense), difficulty(difficulty) {}

void Monster::printInfo(){
    std::cout << "name: " << m_name << "health: " << m_health << std::endl;
}