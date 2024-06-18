#ifndef ZOOPROJEKT_POTION_H
#define ZOOPROJEKT_POTION_H

#include "Item.h"
#include "Hero.h"

class Potion : public Item {
private:
    Hero* m_hero;
public:
    Potion(std::string name, std::string description, Hero* hero);

    void use() override;
};

#endif //ZOOPROJEKT_POTION_H