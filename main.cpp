#include <iostream>
#include "Dungeon.h"

int main() {
    Dungeon dungeon(10, 7);
    dungeon.print();

    char direction;
    while (true) {
        std::cout << "Enter a key to move (or 'q' to quit): ";
        std::cin >> direction;
        if (direction == 'q') {
            break;
        }
        if (dungeon.movePlayer(direction)) { // Kontrola ukončení hry
            break;
        }
        std::cout << std::endl;
        dungeon.print();
    }

    return 0;
}
