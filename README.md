# Breakout Game

Breakout implemented in C++ with SFML for UMGC CMSC 495 Group 3 Capstone.

## Overview

Short video walkthrough (team reference): https://youtu.be/RHrU3I1nsEI?si=UbCCL5GwQ7aRh6ua&t=64

This repository contains **two** executables you can build separately:

| Entry | Sources | Output | Notes |
|--------|---------|--------|--------|
| **Phase I (default root tasks)** | `phase1_main.cpp`, `Game.cpp`, `src/GameManager.cpp`, shared headers | `main.exe` at repo root | Full Breakout Phase I (menu, bricks, HUD, etc.). Uses `src/GameManager.h` and `src/PhysicsManager.h` shared with the prototype. |
| **Earlier prototype** | `src/main.cpp` and related `src/` files | e.g. `src/main.exe` via “build active file” | Separate SFML prototype; see `src/.vscode/` if you use that workflow. |

VS Code configuration for the **Phase I** build lives in the repo root `.vscode/` folder (`tasks.json`, `launch.json`, `c_cpp_properties.json`, `settings.json`). The shared build and run scripts now prefer environment-variable overrides instead of committing machine-specific toolchain paths.

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

This repo targets **C++20 + SFML 3.0.2** on Windows and now supports multiple compatible GCC layouts through the shared PowerShell toolchain resolver. The current scripts can auto-detect common installs such as **MSYS2 UCRT64** and the team’s original **WinLibs GCC 14.2** layout, or you can point the repo at your local install with environment variables. A **CMake** build is included at the repository root ([`CMakeLists.txt`](CMakeLists.txt)) for a more portable setup and for running the automated unit tests via **CTest** (see [`CMakePresets.json`](CMakePresets.json)).

### 1) Toolchain (compiler)

You need a GCC toolchain compatible with your SFML install. The shared scripts currently look for:

- `C:\msys64\ucrt64\bin\g++.exe`
- `C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin\g++.exe`
- `g++.exe` on `PATH`

If you use MSYS2, prefer the **UCRT64** environment so the compiler, debugger, runtime DLLs, and SFML libraries stay aligned.

### 1a) CMake / CTest

For the CMake-based workflow, install `cmake` and `ctest`. On MSYS2 UCRT64, the usual package is:

```bash
pacman -S mingw-w64-ucrt-x86_64-cmake
```

### 2) SFML

You need an SFML 3.0.2 install with this layout:

- `include`
- `lib`
- `bin`

The shared resolver currently checks:

- `C:\msys64\ucrt64`
- `C:\SFML-3.0.2`
- `BREAKOUT_SFML_ROOT`

Download: [SFML 3.0.2](https://www.sfml-dev.org/download/sfml/3.0.2/)

### 3) HUD font (optional pixel font + automatic fallbacks)

The game tries to load fonts in order (first path that exists wins):

1. `assets/fonts/PressStart2P-Regular.ttf` (download [Press Start 2P](https://fonts.google.com/specimen/Press+Start+2P) and place the `.ttf` here)
2. Common Windows fonts: `C:\Windows\Fonts\arial.ttf`, `segoeui.ttf`, or `calibri.ttf`

Missing files are skipped **without** calling SFML on a bad path, so you should not see a font error for a missing asset. If **no** font loads, the main menu uses the **window title** for instructions and **1** / **3** number keys only (see Controls).

### 4) Custom install locations

This repo now prefers **environment-variable overrides** over editing shared project files. Set these locally if your install differs:

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

### CMake build (portable path)

If you want a more portable build setup than the PowerShell scripts, configure the project with CMake from the repo root:

```powershell
cmake --preset default-debug
cmake --build --preset default-debug
```

If your compiler or SFML install is not in the default locations, set `BREAKOUT_GPP` and `BREAKOUT_SFML_ROOT` before configuring.

### VS Code (recommended)

1. Open this folder in VS Code.
2. **Build:** `Terminal` → `Run Build Task` (default build compiles `phase1_main.cpp`, `Game.cpp`, and `src/GameManager.cpp` to `main.exe`).
3. **Run / debug:** `Run` → `Start Debugging` (or F5), configuration **Breakout: Debug (WinLibs + SFML)**.  
   This builds first, then launches `main.exe` with `runtime\` (and optional `BREAKOUT_RUNTIME_BIN`) on `PATH` so bundled DLLs resolve.

The integrated terminal prepends `runtime\` to `PATH` (workspace settings) so after a successful build you can run:

```powershell
.\main.exe
```

If you run the game from a shell that does not include `runtime\` on `PATH`, use `.\scripts\run-game.ps1` or prepend it yourself, e.g. `$env:PATH = "$PWD\runtime;$env:PATH"` before `.\main.exe`.

### Script (outside VS Code)

From the repo root:

```powershell
.\scripts\run-game.ps1
```

### Manual build command

SFML is **not** a system header: you must pass the correct `-I...include` and `-L...lib` flags for your local install, then link `-lsfml-graphics`, `-lsfml-window`, and `-lsfml-system`. Running `g++ *.cpp` or `g++` on sources without those flags produces `SFML/Graphics.hpp: No such file or directory`.

From the repo root, you can use:

```powershell
.\scripts\build-phase1.ps1
```

If you previously built with DLLs beside `main.exe`, delete those leftover `*.dll` files at the repo root so you are not confused by duplicates; new copies go only into `runtime\`.

Example MSYS2 UCRT64 one-liner:

```powershell
C:\msys64\ucrt64\bin\g++.exe -std=c++20 -fdiagnostics-color=always -g -IC:\msys64\ucrt64\include .\phase1_main.cpp .\Game.cpp .\src\GameManager.cpp -LC:\msys64\ucrt64\lib -lsfml-graphics -lsfml-window -lsfml-system -o .\main.exe
```

Bundled MinGW/SFML DLLs live under **`runtime\`** after `build-phase1.ps1`. Windows does not load them from that subfolder automatically: double-clicking **`main.exe` alone will fail** unless `runtime\` is on `PATH` (the run script, VS Code debug/terminal, or a shortcut that sets `PATH`). You can also rely on your compiler and SFML `bin` folders on `PATH` if you are not using the copied DLLs.

## Automated Tests

The repository includes a small **CTest**-registered unit test executable under `tests/` for deterministic helper, state, and collision math:

- `tests/GameHelpersTests.cpp`
- `tests/GameManagerTests.cpp`
- `tests/PhysicsManagerTests.cpp`
- `tests/Collision2DTests.cpp`

Configure and build the tests from the repo root (requires `cmake` / `ctest` on your PATH, for example MSYS2 `mingw-w64-ucrt-x86_64-cmake`):

```powershell
cmake --preset tests-debug
cmake --build --preset tests-debug
ctest --preset tests-debug
```

Or run the wrapper script:

```powershell
.\scripts\build-tests.ps1
```

These tests cover:

- clamp and life-decrement helper behavior
- remaining-brick helper logic
- game manager life reset, decrement, and game-state setters
- physics manager velocity storage and axis reflection behavior
- circle–AABB overlap, separation, axis-correct reflection, wall clamp helpers, and multi-brick resolution loops (`src/Collision2D.h`)

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
- Brick collision detection with circle–AABB resolution (side-aware bounce, separation, multi-hit per frame cap)
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

- The shared toolchain setup is more portable than before, but it is still Windows-focused and depends on a locally installed compatible GCC + SFML toolchain.
- On-screen HUD text needs a loadable font; if none load, fallback menu mode applies (see above).
- Automated tests cover deterministic helpers, manager state, physics reflections, and **pure collision math** (`Collision2D`); full SFML gameplay integration is still verified primarily through manual testing.
- Movement uses per-frame delta time so speed stays consistent if the frame rate changes.
- Brick collision uses a bounded per-frame resolver (side-aware reflection and separation); simultaneous paddle–brick contacts at very high speed can still be ordering-sensitive.
