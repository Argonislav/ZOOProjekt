#include "hero.h"

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