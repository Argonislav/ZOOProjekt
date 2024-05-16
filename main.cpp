#include <iostream>
#include "Dungeon.h"

using namespace std;

int main() {
    int choice;

    do {
        cout << "======== Dungeon Game ========" << endl;
        cout << "1. New game" << endl;
        cout << "2. End" << endl;
        cout << "Choose option:";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Spuštění hry v dungeonu
                Dungeon dungeon(10, 7);
                dungeon.print();

                char direction;
                while (true) {
                    cout << "Enter a key to move (or 'q' to quit): ";
                    cin >> direction;
                    if (direction == 'q') {
                        break;
                    }
                    if (dungeon.movePlayer(direction)) { // Kontrola ukončení hry
                        break;
                    }
                    cout << endl;
                    dungeon.print();
                }
                break;
            }
            case 2:
                cout << "Game was terminated. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 2);

    return 0;
}
