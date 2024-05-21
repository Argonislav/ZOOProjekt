#include "Armor.h"
#include <iostream>

Armor::Armor(std::string name, std::string description, int armorRating)
        : Item(name, description, ItemType::Equipable), m_armorRating(armorRating) {}

int Armor::getArmorRating() {
    return m_armorRating;
}

void Armor::setArmorRating(int armorRating) {
    m_armorRating = armorRating;
}

void Armor::use() {
    std::cout << "You equip the " << getName() << " and gain " << m_armorRating << " armor!" << std::endl;
}