#ifndef ZOOPROJEKT_POTION_H
#define ZOOPROJEKT_POTION_H

#include "Item.h"
#include "Hero.h"

class Potion : public Item {
private:
    Hero* m_hero;
    PotionType m_potionType; // Přidán atribut pro typ lektvaru
public:
    Potion(std::string name, std::string description, Hero* hero, PotionType potionType);

    void use() override;
};

#endif //ZOOPROJEKT_POTION_H