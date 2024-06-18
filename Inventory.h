//
// Created by Lukas Houska on 12.05.2024.
//

#ifndef ZOOPROJEKT_INVENTORY_H
#define ZOOPROJEKT_INVENTORY_H

#include "Item.h"
#include <vector>

class Inventory {
private:
    int capacity;
    int currentItemCount;

public:
    Inventory(int capacity = 0);
    bool addItem(Item* item);
    bool removeItem(Item* item);
    void printItems();
    bool isFull();

    std::vector<Item*> items;
};


#endif //ZOOPROJEKT_INVENTORY_H
