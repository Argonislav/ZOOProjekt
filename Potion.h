#ifndef ZOOPROJEKT_POTION_H
#define ZOOPROJEKT_POTION_H

#include "Item.h"

class Potion : public Item {
public:
    Potion(std::string name, std::string description);

    void use() override;
};

#endif //ZOOPROJEKT_POTION_H