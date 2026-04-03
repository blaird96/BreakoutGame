# Breakout Game - Phase I

Breakout implemented in C++ with SFML for UMGC CMSC 495 Group 3 Capstone.

## Overview

Phase I establishes a playable foundation of Breakout with:

- Paddle movement and wall constraints
- Ball movement and bounce behavior
- Brick grid generation and rendering
- Ball-brick collision and brick deactivation
- Score and lives tracking
- Win and game-over state handling
- Minimal HUD (score, lives, terminal-state messaging)
- Restart flow from terminal states

## Setup Instructions (Windows)

### 1) Install toolchain

Install:

- MinGW GCC 14.2.0 (32-bit DW2 UCRT package)
- SFML 3.0.2 (matching MinGW package)

Download from: [https://www.sfml-dev.org/download/sfml/3.0.2/](https://www.sfml-dev.org/download/sfml/3.0.2/)

### 2) Place dependencies

Extract and place these folders at the root of `C:\`:

- `C:\mingw32`
- `C:\SFML-3.0.2`

### 3) Add compiler to PATH

Add `C:\mingw32\bin` to the user PATH environment variable.

Verify:

```powershell
g++ --version
```

### 4) Optional HUD font

HUD text uses `assets/fonts/PressStart2P-Regular.ttf` when present.  
If the file is missing, gameplay still runs and HUD text rendering is safely skipped.

## Build and Run

### VS Code task (recommended)

Use the default C++ build task configured in `.vscode/tasks.json`, then run `main.exe`.

### Manual build command

```powershell
C:\mingw32\bin\g++.exe -fdiagnostics-color=always -g -IC:\SFML-3.0.2\include .\main.cpp .\Game.cpp -LC:\SFML-3.0.2\lib -lsfml-graphics -lsfml-window -lsfml-system -o .\main.exe
```

Run:

```powershell
.\main.exe
```

## Controls

- `Left Arrow` or `A`: Move paddle left
- `Right Arrow` or `D`: Move paddle right
- `R`: Restart game (only when in Win or Game Over state)

## Features Implemented in Phase I

- Core game loop and rendering pipeline
- Paddle and ball entities
- Brick grid (5x8) with active/inactive lifecycle
- Brick collision detection and bounce response
- Score increment on brick hit
- Lives clamped to zero (no negative values)
- Win condition when all bricks are cleared
- Game over condition when lives are exhausted
- Terminal-state gameplay pause
- HUD support for score, lives, and result text
- Full-state reset for restart flow

## Known Limitations

- Build paths are currently hardcoded for Windows (`C:\mingw32`, `C:\SFML-3.0.2`).
- HUD requires a local font file to render text.
- No automated tests yet (Phase I uses manual verification).
- Gameplay uses frame-dependent movement (no delta-time normalization).
