//
// Created by Lukas Houska on 12.05.2024.
//

#include "Item.h"

Item::Item(std::string name, std::string description, ItemType type, int attackBonus, int healthBonus, int defenseBonus)
        : m_name(name), m_description(description), m_type(type), m_attackBonus(attackBonus), m_healthBonus(healthBonus), m_defenseBonus(defenseBonus) {
}

std::string Item::getName(){
    return m_name;
}

void Item::setName(std::string name) {
    m_name = name;
}

std::string Item::getDescription(){
    return m_description;
}

void Item::setDescription(std::string description) {
    m_description = description;
}

ItemType Item::getType(){
    return m_type;
}

void Item::setType(ItemType type) {
    m_type = type;
}

int Item::getAttackBonus(){
    return m_attackBonus;
}

void Item::setAttackBonus(int attackBonus) {
    m_attackBonus = attackBonus;
}

int Item::getHealthBonus(){
    return m_healthBonus;
}

void Item::setHealthBonus(int healthBonus) {
    m_healthBonus = healthBonus;
}

int Item::getDefenseBonus(){
    return m_defenseBonus;
}

void Item::setDefenseBonus(int defenseBonus) {
    m_defenseBonus = defenseBonus;
}