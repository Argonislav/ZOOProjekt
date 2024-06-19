//
// Created by Lukas Houska on 12.05.2024.
//

#include "Inventory.h"
#include <iostream>

Inventory::Inventory(int capacity) : capacity(capacity), currentItemCount(0) {}

bool Inventory::addItem(Item* item) {
    if (items.size() < capacity) {
        items.push_back(item);
        currentItemCount++; // Zvýšení počtu položek v inventáři
        return true;
    }
    return false;
}

bool Inventory::removeItem(Item* item) {
    // Find the item index in the vector
    for (int i = 0; i < currentItemCount; ++i) {
        if (items[i] == item) {
            // Remove the item from the vector by shifting elements
            items.erase(items.begin() + i);
            currentItemCount--;
            return true;
        }
    }
    return false;
}

void Inventory::printItems() {
    if (currentItemCount == 0) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    std::cout << "Inventory:\n";
    for (int i = 0; i < currentItemCount; ++i) {
        std::cout << i << ". " << items[i]->getName() << " - " << items[i]->getDescription();

        // Zobrazení bonusových statistik pro vybavitelné předměty
        if (items[i]->getType() == ItemType::Equipable) {
            std::cout << " (";
            if (items[i]->getAttackBonus() > 0) {
                std::cout << "+" << items[i]->getAttackBonus() << " Attack";
            }
            if (items[i]->getDefenseBonus() > 0) {
                if (items[i]->getAttackBonus() > 0) {
                    std::cout << ", ";
                }
                std::cout << "+" << items[i]->getDefenseBonus() << " Defense";
            }
            std::cout << ")";

            // Zobrazení informace o vybavení
            if (items[i]->getEquipped()) {
                std::cout << " [Equipped]";
            }
        }
            // Zobrazení informace o typu spotřebního předmětu
        else if (items[i]->getType() == ItemType::Consumable) {
            std::cout << " (Consumable, ";
            switch (items[i]->getPotionType()) {
                case PotionType::Health:
                    std::cout << "Health)";
                    break;
                case PotionType::Attack:
                    std::cout << "Attack)";
                    break;
                case PotionType::Defense:
                    std::cout << "Defense)";
                    break;
            }
        }

        std::cout << std::endl;
    }
}

Item* Inventory::getEquippedItem(ItemType type) {
    for (const auto& item : items) {
        if (item->getType() == type && item->getEquipped()) {
            return item;
        }
    }
    return nullptr;
}