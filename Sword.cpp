#include "Sword.h"
#include "Hero.h"
#include <iostream>

Sword::Sword(std::string name, std::string description, int damage, Hero* hero)
        : Item(name, description, ItemType::Equipable), m_damage(damage), m_hero(hero) {}

int Sword::getDamage() {
    return m_damage;
}

void Sword::setDamage(int damage) {
    m_damage = damage;
}

void Sword::use() {
    if (!getEquipped()) {
        std::cout << "You equip the " << getName() << " and gain " << m_damage << " damage!" << std::endl;
        m_hero->addAttackBonus(getDamage());
        setEquipped(true);
    } else {
        std::cout << "You unequip the " << getName() << " and lose " << m_damage << " damage!" << std::endl;
        m_hero->removeAttackBonus(getDamage());
        setEquipped(false);
    }
}