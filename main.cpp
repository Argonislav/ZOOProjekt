#include <iostream>
#include "Dungeon.h"
#include "Game.h"

using namespace std;

int main() {
    Game* hra = new Game();
    hra->run();


    delete hra;
    return 0;

}
