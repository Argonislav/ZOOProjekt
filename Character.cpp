//
// Created by Jindřich Šantrůček on 12.05.2024.
//

#include <iostream>
#include "Character.h"

Character::Character( std::string name, float health, float attack, float defense)
        : m_name(name), m_health(health), m_attack(attack), m_defense(defense) {}

void Character::takeDamage(float damage) {
    float actualDamage = damage - m_defense;
    if (actualDamage < 0)
        actualDamage = 0;
    m_health -= actualDamage;
    if (m_health <= 0) {
        std::cout << m_name << " has been defeated!" << std::endl;
    }
}

void Character::attack(Character *target) {
    std::cout << m_name << " attacks " << target->m_name << " for " << m_attack - target->m_defense << " damage." << std::endl;
    target->takeDamage(m_attack);
}

bool Character::isAlive(){
    return m_health > 0;
}

// Getter methods
std::string Character::getName() const {
    return m_name;
}

float Character::getHealth() const {
    return m_health;
}

float Character::getAttack() const {
    return m_attack;
}

float Character::getDefense() const {
    return m_defense;
}

void Character::setName(std::string name){
    m_name = name;
}

void Character::setHealth(float health){
    m_health = health;
}

void Character::setAttack(float attack){
    m_attack = attack;
}

void Character::setDefense(float defense){
    m_defense = defense;
}