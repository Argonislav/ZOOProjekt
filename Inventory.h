//
// Created by Lukas Houska on 12.05.2024.
//

#ifndef ZOOPROJEKT_INVENTORY_H
#define ZOOPROJEKT_INVENTORY_H

#include "Item.h"
#include <vector>

class Inventory {
private:
    std::vector<Item> items;
    int capacity;
    int currentItemCount;
};


#endif //ZOOPROJEKT_INVENTORY_H
