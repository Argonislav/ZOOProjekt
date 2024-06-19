#include "Hero.h"

// Constructor
Hero::Hero(std::string name, float health, float attack, float defense)
        : Character(name, health, attack, defense), inventory(nullptr) {}

// Getter for inventory
Inventory* Hero::getInventory() const {
    return inventory;
}

// Setter for inventory
void Hero::setInventory(Inventory* newInventory) {
    inventory = newInventory;
}

// Methods for modifying bonuses
void Hero::addAttackBonus(int bonus) {
    m_attack += bonus;
}

void Hero::removeAttackBonus(int bonus) {
    m_attack -= bonus;
}

void Hero::addDefenseBonus(int bonus) {
    m_defense += bonus;
}

void Hero::removeDefenseBonus(int bonus) {
    m_defense -= bonus;
}