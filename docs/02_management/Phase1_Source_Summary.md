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

## Structure Overview

Primary source files:

- `main.cpp`: Program entry point and game startup
- `Game.h` / `Game.cpp`: Core game loop, update logic, rendering, brick system, HUD, restart flow
- `GameConstants.h`: Tunable constants for window, entities, and brick layout
- `physicsManager.h`: Ball velocity and reflection helpers
- `GameManager.h`: Lives management
- `GameHelpers.h`: Pure helper functions for clamping, life decrement logic, and brick-state checks

Current architecture is intentionally simple and centered around a single `Game` class to support rapid iteration in early phases.

## Testing Approach

Phase 1 verification is primarily manual:

- Gameplay smoke tests while running `main.exe`
- Stepwise feature validation tied to incremental commits
- Manual checklist in `docs/02_management/Phase1_Test_Checklist.md` covering:
  - Paddle movement
  - Ball collisions
  - Brick destruction
  - Score/lives behavior
  - Win/loss states
  - Restart flow

No automated unit or integration test framework is configured yet.

## Limitations

- Build configuration is currently Windows-specific and uses hardcoded dependency paths
- HUD text depends on local font asset availability
- Movement and physics are frame-dependent (no delta-time normalization)
- Collision response remains intentionally basic (simple bounce logic)
- Codebase has limited modular separation and can benefit from further decomposition in later phases
