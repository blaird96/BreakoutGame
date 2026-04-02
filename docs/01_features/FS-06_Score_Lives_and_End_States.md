# FS-06: Score, Lives, and End States

**Category:** Game State Management  
**Priority:** High  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Partial |
| **Primary evidence** | [`main.cpp`](../../main.cpp) lines 15, 54–56 (`lives--`, ball reset) |
| **Gaps** | No score variable or brick-based increments; no game-over when `lives <= 0`; no win when all bricks cleared; no enum/`GameState` machine; lives not shown (FS-08) |

---

## Purpose and scope

**Owns:** Player score, remaining lives, win and loss detection, and transitions from **playing** to terminal states (victory / game over). Coordinates with FS-07 for replay/menu and FS-08 for messaging.

**Out of scope:** Drawing HUD (FS-08); brick storage (FS-04) except via queries/callbacks.

---

## Definitions

- **Life lost:** Prototype: ball `y > 805` decrements `lives` and resets ball (`main.cpp` 54–57).
- **Game over (target):** `lives == 0` after a loss event ends the round.
- **Victory (target):** No active bricks remain (requires FS-04).

---

## Data model and attributes

| Attribute | Prototype | Target |
| --- | --- | --- |
| `lives` | `int`, initialized 3 | Configurable starting lives |
| `score` | absent | `int`, increment on brick break |
| `GameState` | implicit “always play” | e.g. `Menu`, `Playing`, `Win`, `GameOver` |
| `highScore` | absent | Optional persistence (out of blueprint minimum) |

---

## Functional requirements

1. **FS-06.1** The system SHALL decrement remaining lives when the ball is lost per FS-03/FS-05 miss handling.
2. **FS-06.2** The system SHALL reset the ball (and optionally paddle) after a life is lost before play continues.
3. **FS-06.3** The system SHALL maintain a non-negative integer score and increase it when bricks are destroyed (once FS-04/FS-05 exist).
4. **FS-06.4** The system SHALL enter a **win** state when no bricks remain.
5. **FS-06.5** The system SHALL enter a **game over** state when lives reach zero after a loss.
6. **FS-06.6** The system SHALL stop normal gameplay updates in terminal states until restart (FS-07).

---

## Non-functional requirements

- **NFR-01** State transitions SHALL be deterministic from the same input sequence (no race on single-threaded loop).
- **NFR-02** Score and lives SHOULD be obvious to the player via FS-08.

---

## Dependencies

- **Requires:** FS-03 miss detection; FS-04/FS-05 for score and win.
- **Blocks:** FS-07 meaningful restart; FS-08 text content.

---

## Interfaces and events

**Events (conceptual)**

- `onBallLost()` → decrement life, maybe reset entities.
- `onBrickDestroyed(points)` → add score.
- `onAllBricksCleared()` → win.
- `onNoLivesRemaining()` → game over.

**As-built:** Only inline `lives--` inside miss branch.

---

## Acceptance criteria

- [ ] Losing the ball reduces lives by one and respawns ball at agreed position.
- [ ] Score increases when a brick is cleared (post FS-04).
- [ ] Clearing all bricks stops loss-of-life from being the win condition and shows win flow (FS-07/08).
- [ ] At zero lives, gameplay stops and game-over flow appears (FS-07/08).
- [ ] (Prototype gap) Current build allows lives to go negative unless guarded — **must fix** for Tier 1 done.

---

## Implementation notes

**As-built:** `int lives = 3`; miss decrements without floor check or game end (`main.cpp` 15, 54–56).

**Target:** `if (lives > 0) { lives--; ... } else { transitionToGameOver(); }` or decrement after check; central `GameState` switch in main loop.

---

## Testing considerations

- Manual: lose ball repeatedly; verify count stops at 0 and end state triggers after fix.
- Manual: clear all bricks (once implemented); verify win.
- Unit: `applyScore`, `loseLife` pure functions if extracted.

---

## Documentation and evidence

- Screenshot: HUD showing score and lives (when FS-08 lands).
- Report section: rules for points per brick.

---

## Open questions and decisions

- Points per brick vs. per row; bonus for clearing level.
- Whether extra life at score threshold is in scope (stretch).
