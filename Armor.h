#ifndef ZOOPROJEKT_ARMOR_H
#define ZOOPROJEKT_ARMOR_H

#include "Item.h"
#include "Hero.h"

class Armor : public Item {
private:
    int m_armorRating;
    Hero* m_hero;

public:
    Armor(std::string name, std::string description, int armorRating, Hero* hero);

    int getArmorRating();
    void setArmorRating(int armorRating);

    void use() override;
};

#endif //ZOOPROJEKT_ARMOR_H