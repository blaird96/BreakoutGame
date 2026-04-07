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

This repo is configured for a **WinLibs GCC 14.2** toolchain plus **SFML 3.0.2** built for the same MinGW flavor.

### 1) Toolchain (compiler)

Use the WinLibs distribution at:

- `C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin`

That folder should contain `g++.exe`, `gdb.exe`, and the runtime DLLs MinGW links against.

Optional: you can also install **MSYS2** for a separate `g++`, but the **VS Code build task** in this repo targets WinLibs so it matches the SFML prebuilt binaries.

### 2) SFML

Extract the **SFML 3.0.2 GCC 14.2 MinGW 64-bit** package so you have:

- `C:\SFML-3.0.2\include`
- `C:\SFML-3.0.2\lib`
- `C:\SFML-3.0.2\bin` (SFML DLLs)

Download: [SFML 3.0.2](https://www.sfml-dev.org/download/sfml/3.0.2/)

### 3) Optional HUD font

HUD text uses `assets/fonts/PressStart2P-Regular.ttf` when present.  
If the file is missing, gameplay still runs and HUD text rendering is safely skipped.

### 4) Custom install locations

If your paths differ, update:

- `.vscode/tasks.json` (compiler and `-I` / `-L` flags)
- `.vscode/c_cpp_properties.json` (IntelliSense include path and `compilerPath`)
- `.vscode/launch.json` and `.vscode/settings.json` (PATH entries for runtime)
- `scripts/run-game.ps1` (PATH entries)

## Build and Run

### VS Code (recommended)

1. Open this folder in VS Code.
2. **Build:** `Terminal` → `Run Build Task` (default build compiles `main.cpp` and `Game.cpp` to `main.exe`).
3. **Run / debug:** `Run` → `Start Debugging` (or F5), configuration **Breakout: Debug (WinLibs + SFML)**.  
   This builds first, then launches `main.exe` with WinLibs and SFML on `PATH` so DLLs resolve.

The integrated terminal is also configured (workspace settings) so after a successful build you can run:

```powershell
.\main.exe
```

### Script (outside VS Code)

From the repo root:

```powershell
.\scripts\run-game.ps1
```

### Manual build command

```powershell
C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin\g++.exe -fdiagnostics-color=always -g -IC:\SFML-3.0.2\include .\main.cpp .\Game.cpp -LC:\SFML-3.0.2\lib -lsfml-graphics -lsfml-window -lsfml-system -o .\main.exe
```

If you run `main.exe` by double-clicking, ensure **WinLibs** `mingw64\bin` and **SFML** `bin` are on your `PATH`, or use the script / VS Code launch configuration above.

## Controls

### Main menu

- `Up` / `Down`: Move selection
- `Enter`: Choose Play, Settings, or Quit

### Settings

- `Up` / `Down`: Select Paddle speed, Ball speed, or Back
- `Left` / `Right`: Decrease or increase speed (50% to 200% of defaults)
- `Enter` or `Esc`: Back to main menu (when **Back** is highlighted, `Enter` also returns)

### In game

- `Left Arrow` or `A`: Move paddle left
- `Right Arrow` or `D`: Move paddle right
- `R`: Restart match (only when in Win or Game Over state)
- `Esc`: Return to main menu (only when in Win or Game Over state)

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
- Main menu and settings screen for paddle and ball speed multipliers

## Known Limitations

- Build and runtime paths are configured for this machine layout (`C:\winlibs-...`, `C:\SFML-3.0.2`).
- HUD requires a local font file to render text.
- No automated tests yet (Phase I uses manual verification).
- Gameplay uses frame-dependent movement (no delta-time normalization).
