# Implementation Plan — Dark Age 

**Spec Summary**
- **Movement**: `up`, `down`, `left`, `right`  (mapped from **W/A/S/D**).
- **Single player**
- **Equipment**: `wear armor` / `remove armor` (simple toggle).
- **Combat**: **player acts first**; **enemies do not move** (they only attack if already adjacent).
- **Conversation**: `talk` to an adjacent NPC.
- **Help menu shows exactly**: `quit`, `inventory` (show items/equipment), `health` (show HP).

---

## Feature 1: New Game & Character Creation

**Trigger**: Main menu → **New Game**.  
**Inputs**: player name (string), player class (string: Warrior/Rogue/Mage).

**Flow**
1. `GameManager::run()` → user choose **New Game** → `actionStartNew_()`.
2. Prompts for name/class.
3. `game->startNew(name, class)`:
    - Allocate the single `Player`.
    - Create a simple `Map` (grid).
    - Spawn a few **stationary** `Enemy` objects and some `NPC` objects.
    - Set `running=true`, `turnCount=0`.
4. Call `game->render()` to show a brief intro/state snapshot.

**State Changes**: `player`, `map`, `enemies`, `npcs`, `running`, `turnCount`.  
**Done when**: the session is active and the user can **Continue**.

**Functions**: `GameManager::actionStartNew_()`, `Game::startNew(...)`, `Game::render()`.

---

## Feature 2: Movement (up/down/left/right via W/A/S/D)

**Trigger**: In-session command: `w`, `a`, `s`, or `d`.  
**Mapping**:
- `w` → **up** → `Game::tryMoveUp()`
- `a` → **left** → `Game::tryMoveLeft()`
- `s` → **down** → `Game::tryMoveDown()`
- `d` → **right** → `Game::tryMoveRight()`

**Flow**
1. `GameManager::actionContinue_()` reads the command line.
2. `Game::processCommand(cmd)` maps to movement methods above.
3. `Game::handleMovement_("up"|"down"|"left"|"right")` validates map bounds/walls.
4. Call `update()` to complete the turn; `render()` prints the new state.

**State Changes**: player position on `Map`; `turnCount++`.  
**Done when**: one turn has elapsed (player phase + enemy phase).

**Functions**: `Game::processCommand`, `Game::tryMoveUp/Down/Left/Right`, `Game::update()`, `Game::render()`.

---

## Feature 3: Equipment — Wear/Remove Armor

**Trigger**: `wear armor` (or `remove armor`).  
**Assumption**: Armor exists by default (no pickup).

**Flow**
1. `Game::processCommand("wear armor")` → `tryWearArmor()`; sets `equippedArmor=true` if not already set.
2. `remove armor` → `tryRemoveArmor()`; sets `equippedArmor=false`.
3. Armor provides a flat damage reduction (e.g., −1 per enemy hit).
4. After command, `update()` advances the turn and `render()` prints status.

**State Changes**: `Player::equippedArmor` (bool), effective defense.  
**Functions**: `Game::tryWearArmor()`, `Game::tryRemoveArmor()`, `Game::update()`, `Game::render()`.

---

## Feature 4: Turn-Based Combat (Player First; Enemies Stationary)

**Trigger**: `attack` when an enemy is adjacent/in range.  
**Turn Order**
1. **Player phase**: resolve player intent (e.g., `attack`).
2. **Enemy phase**: **stationary** enemies **do not move**; if adjacent, they attack; otherwise they skip.
3. End: `cleanupDeadEntities_()`, increment `turnCount`.

**Flow**
1. `Game::processCommand("attack")` → `tryAttack()` (sets player attack intent).
2. `Game::update()`:
    - `resolvePlayerPhase_()` → `handleCombat_()` applies player damage first.
    - `resolveEnemyPhase_()` → adjacent enemies (only) apply damage.
3. `cleanupDeadEntities_()` removes defeated enemies; `render()` prints summary.

**State Changes**: Enemy HP, Player HP, `turnCount++`.  
**Game Over**: if Player HP ≤ 0 → `running=false`.

**Functions**: `Game::tryAttack()`, `Game::update()`, `Game::render()`.

---

## Feature 5: Conversation with NPC

**Trigger**: `talk` when adjacent to an NPC.  
**Flow**
1. `Game::processCommand("talk")` → `tryTalkToNPC()` checks adjacency.
2. Print one line of dialog and up to 2–3 numbered replies.
3. Record a simple flag (e.g., `npcMet=true`) to unlock a hint or tiny buff.
4. Call `update()` to finish the turn; `render()` shows the chosen line.

**State Changes**: Per-NPC conversation flags.  
**Functions**: `Game::tryTalkToNPC()`, `Game::update()`, `Game::render()`.

---

## Feature 6: Help Menu & Status Commands

**Help Menu Requirement**: when the user chooses **Help** in the main menu (or types `help` in-session), it must list exactly:
- `quit` — exit the session
- `inventory` — show items/equipment
- `health` — show current HP

**Status Commands**
- `inventory` → `Game::showInventory()`
- `health` → `Game::showHealth()`

**Functions**: `GameManager::actionHelp_()`, `Game::showInventory() const`, `Game::showHealth() const`.

---

## Update/Render Loop Contract

**`Game::processCommand(input)`**  
Parses `input` to one of: `tryMoveUp/Down/Left/Right`, `tryAttack`, `tryWearArmor`, `tryRemoveArmor`, `tryTalkToNPC`, `showInventory`, `showHealth`, or `quit`.

**`Game::update()`**
1. `resolvePlayerPhase_()` — act on the chosen intent.
2. `resolveEnemyPhase_()` — adjacent enemies attack; others skip (no movement).
3. `cleanupDeadEntities_()`; `turnCount++`.

**`Game::render() const`**  
Print compact snapshot: turn, player HP, armor state, tile description, nearby enemies/NPCs.


