#include <iostream>
#include "Hero.h"
#include "Monster.h"

int main() {
    Hero* hero= new Hero("Brave Knight", 100, 20, 10);
    Monster* monster = new Monster("Evil Goblin", 50, 15, 5);

    hero->attack(monster);
    monster->printInfo();

    delete hero;
    delete monster;
    return 0;
}