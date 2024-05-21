#ifndef ZOOPROJEKT_SWORD_H
#define ZOOPROJEKT_SWORD_H

#include "Item.h"

class Sword : public Item {
private:
    int m_damage;

public:
    Sword(std::string name, std::string description, int damage);

    int getDamage();
    void setDamage(int damage);

    void use() override; // Implement the virtual use function
};

#endif //ZOOPROJEKT_SWORD_H