#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <memory>
#include <string>

class Game;

/**
 * GameManager
 * -----------
 * Orchestrates menu flow and routes user input to the Game.
 * Menu options: New Game, Continue, Help, Quit.
 * While continuing, accepts commands:
 *   w/a/s/d (move up/left/down/right), attack, wear armor, remove armor,
 *   talk, inventory, health, help, quit.
 */
class GameManager {
private:
    std::unique_ptr<Game> game;

    // Small I/O helpers (declared; define later)
    std::string prompt(const std::string& label) const;
    int promptInt(const std::string& label, int minVal, int maxVal) const; // optional use

    // Menu actions
    void actionStartNew_();
    void actionContinue_();
    void actionHelp_() const;

    // Loop utilities
    void showMainMenu_() const;
    int  readMenuChoice_() const;

public:
    GameManager();
    explicit GameManager(std::unique_ptr<Game> initialGame);
    ~GameManager() = default;

    // Entry point for the program
    void run();
};

#endif // GAME_MANAGER_H
