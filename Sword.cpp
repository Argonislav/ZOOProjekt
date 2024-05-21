#include "Sword.h"
#include <iostream>

Sword::Sword(std::string name, std::string description, int damage)
        : Item(name, description, ItemType::Equipable), m_damage(damage) {}

int Sword::getDamage() {
    return m_damage;
}

void Sword::setDamage(int damage) {
    m_damage = damage;
}

void Sword::use() {
    std::cout << "You swing the " << getName() << " and deal " << m_damage << " damage!" << std::endl;
}