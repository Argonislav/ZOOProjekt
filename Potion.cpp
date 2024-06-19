#include "Potion.h"
#include <iostream>

Potion::Potion(std::string name, std::string description, Hero* hero, PotionType potionType)
        : Item(name, description, ItemType::Consumable), m_hero(hero), m_potionType(potionType) {
    setPotionType(potionType); // Nastavení typu lektvaru
}

void Potion::use() {
    std::cout << "You drink the " << getName() << "!\n";
    switch (m_potionType) {
        case PotionType::Health:
            std::cout << "It restores 10 health!\n";
            m_hero->setHealth(m_hero->getHealth() + 10);
            break;
        case PotionType::Attack:
            std::cout << "It increases your attack by 5!\n";
            m_hero->setAttack(m_hero->getAttack() + 5);
            break;
        case PotionType::Defense:
            std::cout << "It increases your defense by 3!\n";
            m_hero->setDefense(m_hero->getDefense() + 3);
            break;
    }
}