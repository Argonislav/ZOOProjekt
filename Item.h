//
// Created by Oldrich Houska on 12.05.2024.
//

#ifndef ZOOPROJEKT_ITEM_H
#define ZOOPROJEKT_ITEM_H


#include <string>

enum class ItemType {
    Consumable, // Spotřebitelná položka
    Equipable  // Vybavitelná položka
};

class Item {
private:
    std::string name;
    std::string description;
    ItemType type;
    double weight;
    int attackBonus;
    int healthBonus;
    int defenseBonus;
};

#endif //ZOOPROJEKT_ITEM_H
