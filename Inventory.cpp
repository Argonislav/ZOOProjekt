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
        std::cout << "Inventory is empty." << std::endl;
        return;
    }
    else{
        std::cout << "Inventory:" << std::endl;
        for (const auto& item : items) {
            std::cout << item->getName() << " - " << item->getDescription() << std::endl;
        }
    }
}

bool Inventory::isFull(){
    return currentItemCount >= capacity;
}