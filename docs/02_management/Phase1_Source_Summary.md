# Phase 1 Source Summary

## Implemented Features

Phase 1 delivers the playable core loop for Breakout:

- Paddle movement with left/right bounds
- Ball movement and boundary reflections
- Brick grid generation (5x8) with active/inactive brick state
- Ball-to-brick collision detection with brick deactivation and bounce response
- Score tracking on brick hits
- Lives tracking with lower bound protection (no negative lives)
- Win detection when no active bricks remain
- Game-over detection when lives reach zero
- HUD rendering for score/lives and terminal-state messages
- Restart support from win/game-over states
- Main menu and settings screen support
- Mouse-click menu interaction
- Paddle-hit angle steering and randomized serve variation
- Delta-time based movement updates
- Font fallback behavior when no HUD font can be loaded

## Structure Overview

Primary source files:

- `phase1_main.cpp`: Program entry point and game startup (`main()` delegates to `Game::run()`)
- `Game.h` / `Game.cpp`: Core game loop, input handling, menu/settings flow, update logic, rendering, brick system, HUD, and restart flow
- `GameConstants.h`: Tunable constants for window, entities, and brick layout
- `src/PhysicsManager.h`: Ball velocity and reflection helpers
- `src/GameManager.h` / `src/GameManager.cpp`: Lives management and simple game-state storage
- `GameHelpers.h`: Pure helper functions for clamping, life decrement logic, and brick-state checks

Current architecture is intentionally simple and centered around a single `Game` class to support rapid iteration in early phases.

## Testing Approach

Phase 1 verification now uses both automated and manual testing:

- Automated unit tests via `CMake` + `CTest` for deterministic helper and state logic in:
  - `tests/GameHelpersTests.cpp`
  - `tests/GameManagerTests.cpp`
  - `tests/PhysicsManagerTests.cpp`
- Build verification through `scripts/build-phase1.ps1`
- Gameplay smoke tests while running `main.exe`
- Stepwise feature validation tied to incremental commits
- Manual checklist in `docs/02_management/Phase1_Test_Checklist.md` covering:
  - Paddle movement
  - Ball collisions
  - Brick destruction
  - Score/lives behavior
  - Win/loss states
  - Restart flow
- Recorded manual execution evidence in `docs/02_management/Phase1_Test_Checklist.md`

## Limitations

- Build setup is more portable than the original hardcoded layout, but it remains Windows-focused and still depends on a locally installed compatible GCC + SFML toolchain
- HUD text depends on local font asset availability
- Brick collision response remains intentionally basic (simple bounce logic)
- Automated tests currently focus on deterministic helper and state behavior; full gameplay interaction remains primarily manual
- Codebase has limited modular separation and can benefit from further decomposition in later phases
