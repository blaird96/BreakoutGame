# Breakout Game

Breakout implemented in C++ with SFML for UMGC CMSC 495 Group 3 Capstone.

## Overview

Short video walkthrough (team reference): https://youtu.be/RHrU3I1nsEI?si=UbCCL5GwQ7aRh6ua&t=64

This repository contains **two** executables you can build separately:

| Entry | Sources | Output | Notes |
|--------|---------|--------|--------|
| **Phase I (default root tasks)** | `phase1_main.cpp`, `Game.cpp`, `src/GameManager.cpp`, shared headers | `main.exe` at repo root | Full Breakout Phase I (menu, bricks, HUD, etc.). Uses `src/GameManager.h` and `src/PhysicsManager.h` shared with the prototype. |
| **Earlier prototype** | `src/main.cpp` and related `src/` files | e.g. `src/main.exe` via “build active file” | Separate SFML prototype; see `src/.vscode/` if you use that workflow. |

VS Code configuration for the **Phase I** build lives in the repo root `.vscode/` folder (`tasks.json`, `launch.json`, `c_cpp_properties.json`, `settings.json`). Edit those files if your compiler or SFML paths differ—avoid pasting machine-specific paths into this README.

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

### 3) HUD font (optional pixel font + automatic fallbacks)

The game tries to load fonts in order (first path that exists wins):

1. `assets/fonts/PressStart2P-Regular.ttf` (download [Press Start 2P](https://fonts.google.com/specimen/Press+Start+2P) and place the `.ttf` here)
2. Common Windows fonts: `C:\Windows\Fonts\arial.ttf`, `segoeui.ttf`, or `calibri.ttf`

Missing files are skipped **without** calling SFML on a bad path, so you should not see a font error for a missing asset. If **no** font loads, the main menu uses the **window title** for instructions and **1** / **3** number keys only (see Controls).

### 4) Custom install locations

This repo now prefers **environment-variable overrides** over editing shared project files.
Set these locally if your install differs:

- `BREAKOUT_GPP`: full path to `g++.exe`
- `BREAKOUT_GDB`: full path to `gdb.exe`
- `BREAKOUT_SFML_ROOT`: folder containing `include`, `lib`, and `bin`
- `BREAKOUT_RUNTIME_BIN`: optional semicolon-separated runtime DLL path(s)

Examples:

- MSYS2 UCRT64:
  - `BREAKOUT_GPP=C:\msys64\ucrt64\bin\g++.exe`
  - `BREAKOUT_GDB=C:\msys64\ucrt64\bin\gdb.exe`
  - `BREAKOUT_SFML_ROOT=C:\msys64\ucrt64`
  - `BREAKOUT_RUNTIME_BIN=C:\msys64\ucrt64\bin`
- Standalone SFML + WinLibs:
  - `BREAKOUT_GPP=C:\winlibs-...\mingw64\bin\g++.exe`
  - `BREAKOUT_GDB=C:\winlibs-...\mingw64\bin\gdb.exe`
  - `BREAKOUT_SFML_ROOT=C:\SFML-3.0.2`
  - `BREAKOUT_RUNTIME_BIN=C:\winlibs-...\mingw64\bin;C:\SFML-3.0.2\bin`

If those variables are not set, the build and run scripts fall back to common locations such as `C:\msys64\ucrt64` and the original WinLibs path.

## Build and Run

### VS Code (recommended)

1. Open this folder in VS Code.
2. **Build:** `Terminal` → `Run Build Task` (default build compiles `phase1_main.cpp`, `Game.cpp`, and `src/GameManager.cpp` to `main.exe`).
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

SFML is **not** a system header: you must pass `-IC:\SFML-3.0.2\include` (or your install) and link with `-L.../lib` plus `-lsfml-graphics`, `-lsfml-window`, `-lsfml-system`. Running `g++ *.cpp` or `g++` on sources without those flags produces `SFML/Graphics.hpp: No such file or directory`.

From the repo root, you can use:

```powershell
.\scripts\build-phase1.ps1
```

Or the equivalent one-liner:

```powershell
C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin\g++.exe -std=c++20 -fdiagnostics-color=always -g -IC:\SFML-3.0.2\include .\phase1_main.cpp .\Game.cpp .\src\GameManager.cpp -LC:\SFML-3.0.2\lib -lsfml-graphics -lsfml-window -lsfml-system -o .\main.exe
```

If you run `main.exe` by double-clicking, ensure **WinLibs** `mingw64\bin` and **SFML** `bin` are on your `PATH`, or use the script / VS Code launch configuration above.

## Controls

### Main menu

- `Up` / `Down`: Move selection
- `Enter` (main or numpad): Choose Play, Settings, or Quit

### Settings

- `Up` / `Down`: Select Paddle speed, Ball speed, or Back
- `Left` / `Right`: Decrease or increase speed (50% to 200% of defaults)
- `Enter` / `Esc` / `Backspace`: Back to main menu (or choose **Back** and press `Enter`)

### In game

- `Left Arrow` or `A`: Move paddle left
- `Right Arrow` or `D`: Move paddle right
- `Esc`: Return to main menu (during active play, or from win/loss)
- `R` or `Space`: Start a new match (**only** when in Win or Game Over state; ignored during active play)
- `M`: Return to main menu (**only** when in Win or Game Over state)

### No on-screen font (fallback mode)

If no font file could be loaded, the window title shows **1 Play** and **3 Quit**. Settings are not available in this mode.

If a key seems to do nothing, **click the game window** so it has keyboard focus (required for SFML to read the keyboard). After win/loss, menu and restart use **real-time key polling** with both logical keys and physical scancodes, so `Esc` / `M` work even when `KeyPressed` events are unreliable.

Some editors still capture `Esc` while debugging; use **`M`** for menu, or run `main.exe` outside the IDE.

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
- Paddle hits steer the ball (English) by where it strikes the paddle; each serve adds small random angle and speed variation

## Known Limitations

- Build and runtime paths are configured for this machine layout (`C:\winlibs-...`, `C:\SFML-3.0.2`).
- On-screen HUD text needs a loadable font; if none load, fallback menu mode applies (see above).
- No automated tests yet (Phase I uses manual verification).
- Movement uses per-frame delta time so speed stays consistent if the frame rate changes.
