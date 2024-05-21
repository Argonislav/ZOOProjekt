#ifndef ZOOPROJEKT_ARMOR_H
#define ZOOPROJEKT_ARMOR_H

#include "Item.h"

class Armor : public Item {
private:
    int m_armorRating;

public:
    Armor(std::string name, std::string description, int armorRating);

    int getArmorRating();
    void setArmorRating(int armorRating);

    void use() override;
};

#endif //ZOOPROJEKT_ARMOR_H