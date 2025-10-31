#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <vector>

// Forward declarations to avoid circular dependencies
class Player;
class Enemy;
class Map;
class NPC;

class Game {
private:
    std::unique_ptr<Player> player;                // Owned player
    std::unique_ptr<Map> map;                      // Owned world map
    std::vector<std::unique_ptr<Enemy>> enemies;   // Stationary enemies
    std::vector<std::unique_ptr<NPC>> npcs;        // NPCs for simple dialog

    bool running = false;                          // Is a game session active?
    int turnCount = 0;                             // Number of turns elapsed

    // --- Internal helpers (to implement in .cpp later) ---
    void resolvePlayerPhase_();                    // resolves the player's chosen intent
    void resolveEnemyPhase_();                     // enemies attack if adjacent; they cannot move
    void handleMovement_(const std::string& dir);  // "up" | "down" | "left" | "right"
    void handleCombat();                          // resolves combat based on the set intent
    void cleanupDeadEntities_();                   // remove defeated enemies, etc.
    bool isEnemyAdjacent_() const;                 // helper for adjacency checks

public:
    // --- Lifecycle ---
    Game() = default;
    ~Game() = default;

    // Start new session with character setup
    void startNew(const std::string& playerName, const std::string& playerClass);

    // Main loop hooks
    void processCommand(const std::string& input); // Parse a command string
    void update();                                 // Advance one full turn (player then enemies)
    void render() const;                           // Print a textual snapshot (location, HP, etc.)

    // Session control
    bool isRunning() const { return running; }
    void quit() { running = false; }

    //Introspection
    int  getTurnCount() const { return turnCount; }

    // Movement API (W/A/S/D mapped to these)
    void tryMoveUp();
    void tryMoveDown();
    void tryMoveLeft();
    void tryMoveRight();

    // Combat & equipment
    void tryAttack();
    void tryWearArmor();
    void tryRemoveArmor();

    // Interaction & status
    void tryTalkToNPC();
    void showInventory() const;
    void showHealth() const;
};

#endif // GAME_H
