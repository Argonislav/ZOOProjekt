#include "Potion.h"
#include <iostream>

Potion::Potion(std::string name, std::string description)
        : Item(name, description, ItemType::Consumable) {}

void Potion::use() {
    std::cout << "You drink the " << getName() << " and it takes effect!" << std::endl;
    // Implement potion effects based on its type (e.g., healing, strength boost)
}