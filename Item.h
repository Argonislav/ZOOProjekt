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

public:
    Item(const std::string& name, const std::string& description, ItemType type, int attackBonus = 0, int healthBonus = 0, int defenseBonus = 0);

    std::string getName();
    void setName(std::string name);

    std::string getDescription();
    void setDescription(std::string description);

    ItemType getType();
    void setType(ItemType type);

    int getAttackBonus();
    void setAttackBonus(int attackBonus);

    int getHealthBonus();
    void setHealthBonus(int healthBonus);

    int getDefenseBonus();
    void setDefenseBonus(int defenseBonus);

    virtual void use() = 0;
};

#endif //ZOOPROJEKT_ITEM_H
