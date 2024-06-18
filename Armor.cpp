#include "Armor.h"
#include "Hero.h"
#include <iostream>

Armor::Armor(std::string name, std::string description, int armorRating, Hero* hero)
        : Item(name, description, ItemType::Equipable), m_armorRating(armorRating), m_hero(hero) {}

int Armor::getArmorRating() {
    return m_armorRating;
}

void Armor::setArmorRating(int armorRating) {
    m_armorRating = armorRating;
}

void Armor::use() {
    std::cout << "You equip the " << getName() << " and gain " << m_armorRating << " armor!" << std::endl;
        m_hero->setDefense(m_hero->getDefense() + getArmorRating());

}