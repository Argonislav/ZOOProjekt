//
// Created by Lukas Houska on 12.05.2024.
//

#include "Inventory.h"
#include <iostream>

Inventory::Inventory(int capacity) : capacity(capacity), currentItemCount(0) {}

bool Inventory::addItem(Item* item) {
    if (isFull()) {
        return false;
    }
    items.push_back(item);
    currentItemCount++;
    return true;
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
    std::cout << "Inventory:" << std::endl;
    for (int i = 0; i < currentItemCount; ++i) {
        std::cout << i + 1 << ". " << items[i]->getName() << std::endl;
    }
}

bool Inventory::isFull(){
    return currentItemCount >= capacity;
}