# FS-07: Start Menu, Restart, and Game Flow Control

**Category:** User Experience / Game State  
**Priority:** Medium to High  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Not started |
| **Primary evidence** | [`main.cpp`](../../main.cpp) runs a single continuous loop; no menu or restart keys |
| **Gaps** | No title/menu screen; no pause; no “press key to restart” after win/loss; state machine not implemented |

---

## Purpose and scope

**Owns:** High-level game flow — boot into menu or straight to play (team choice), start new game, pause (optional), restart after win/loss, and return to menu if desired.

**Out of scope:** Per-frame simulation (FS-03), rendering HUD elements detail (FS-08 implements drawing; FS-07 defines when to show states).

---

## Definitions

- **Session:** From executable launch to exit.
- **Round:** One ball in play until miss or win (usage optional).
- **New game:** Resets score, lives, bricks, ball, paddle to initial conditions.

---

## Data model and attributes (target)

| Attribute | Description |
| --- | --- |
| `GameState` | Enum: `Title`, `Playing`, `Paused`, `Win`, `GameOver` |
| `menuSelection` | If menu has multiple items |
| `pauseOverlayActive` | Bool |
| Key bindings | e.g. `Enter` start, `R` restart, `Esc` pause/menu — **TBD** |

---

## Functional requirements

1. **FS-07.1** The system SHALL offer a clear way to begin gameplay from an initial state (menu or instructional splash).
2. **FS-07.2** The system SHALL restart the game after win or loss so the player can play again without relaunching the executable.
3. **FS-07.3** The system SHALL transition explicitly among menu, playing, win, and game-over states per FS-06 signals.
4. **FS-07.4** (Optional / stretch) The system MAY support pause/resume during play.
5. **FS-07.5** (Target) The system SHOULD ignore gameplay input in non-playing states except for acknowledged menu keys.

---

## Non-functional requirements

- **NFR-01** State changes SHOULD be immediate after user confirmation (no long blocking on disk).

---

## Dependencies

- **Requires:** FS-06 for win/loss signals; FS-01 window/events; FS-08 for user-visible prompts.
- **Coordinates with:** FS-04 brick reset on new game.

---

## Interfaces and events

**Inputs:** Keyboard (and optionally mouse) for menu/restart; `sf::Event::KeyPressed` often clearer than `isKeyPressed` for one-shot actions.

**Outputs:** Calls to reset subsystems; sets `GameState` for HUD rendering.

---

## Acceptance criteria

- [ ] Cold start never drops player into broken state (either menu or paused-ready play per design).
- [ ] After win, player can start again (full reset).
- [ ] After game over, player can start again without closing app.
- [ ] Documented keys for start/restart/pause appear in User Guide (FS-12).

---

## Implementation notes

**As-built:** Game always in implicit “playing”; closing window only exit.

**Target:** Top-level `switch(gameState)` before physics; `resetGame()` function setting lives/score/bricks/ball/paddle.

---

## Testing considerations

- Manual: win once, restart, verify score/lives/bricks reset.
- Manual: game over, restart, same checks.
- Regression: no duplicate event firing causing double reset.

---

## Documentation and evidence

- Screenshots: title screen, win screen, game over screen.
- Short flow diagram in Final Report.

---

## Open questions and decisions

- Menu art vs. plain text SFML `Text`.
- Whether ESC quits or opens menu on Windows.
