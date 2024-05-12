//
// Created by Jindřich Šantrůček on 12.05.2024.
//

#ifndef UNTITLED_CHARACTER_H
#define UNTITLED_CHARACTER_H


#include <string>

class Character {
protected:
    std::string m_name;
    float m_health;
    float m_attack;
    float m_defense;
public:
    Character(std::string name, float health, float attack, float defense);
    void takeDamage(float damage);
    void attack(Character *target);
    bool isAlive();
};


#endif //UNTITLED_CHARACTER_H
