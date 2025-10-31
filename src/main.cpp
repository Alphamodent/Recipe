#include <iostream>
#include <string>
#include "../include/GameManager.h"
#include "../include/Game.h"

using namespace std;

// Display a simple banner or splash screen
static void banner() {
    cout << "=============================\n";
    cout << "       DARK AGE RPG     \n";
    cout << "=============================\n";
}

int main() {
    banner();
    // Construct a manager and enter program loop.
    GameManager manager;
    manager.run();
    return 0;
}
