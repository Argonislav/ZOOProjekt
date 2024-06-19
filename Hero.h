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

    // Methods for modifying bonuses
    void addAttackBonus(int bonus);
    void removeAttackBonus(int bonus);
    void addDefenseBonus(int bonus);
    void removeDefenseBonus(int bonus);

    Inventory* inventory;
};

#endif // HERO_H