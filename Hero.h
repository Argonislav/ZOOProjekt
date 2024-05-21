#ifndef HERO_H
#define HERO_H

#include <string>
#include "Character.h"
#include "Inventory.h"

class Hero : public Character {
public:
    // Constructor
    Hero(std::string name, float health, float attack, float defense);

    // Inventory accessors (getters and setters)
    Inventory* getInventory() const;
    void setInventory(Inventory* newInventory);

private:
    Inventory* inventory; // Inventory pointer
};

#endif // HERO_H