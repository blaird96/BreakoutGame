# Development Guide

## Local Environment Setup

- Primary supported environment is **Windows** with **C++20 + SFML 3.0.2**.
- Recommended compiler/runtime layout is **MSYS2 UCRT64** or a compatible WinLibs GCC install.
- Optional local overrides:
  - `BREAKOUT_GPP` (path to `g++.exe`)
  - `BREAKOUT_GDB` (path to `gdb.exe`)
  - `BREAKOUT_SFML_ROOT` (folder containing `include`, `lib`, `bin`)
  - `BREAKOUT_RUNTIME_BIN` (extra runtime DLL paths, semicolon-separated)

## Installing Dependencies

- Required:
  - GCC toolchain (C++20-capable)
  - SFML 3.0.2
- Optional but recommended:
  - CMake + CTest (for preset-based test workflow)
- On MSYS2 UCRT64, CMake can be installed with:
  - `pacman -S mingw-w64-ucrt-x86_64-cmake`

## Running the Project Locally

- VS Code workflow (recommended on Windows):
  1. Open repository root in VS Code.
  2. Run default build task to produce `main.exe`.
  3. Start debug config **Breakout: Debug (WinLibs + SFML)** or run `.\main.exe` after PATH is configured.
- Script workflow (Windows):
  - Build: `.\scripts\build-phase1.ps1`
  - Run: `.\scripts\run-game.ps1`
- Script workflow (macOS/Linux):
  - Build: `bash ./scripts/build-phase1.sh`
  - Requires `BREAKOUT_SFML_ROOT` if SFML is not in default Homebrew locations.

## Running Tests

- Unit tests are under `tests/` and are intended to run through CMake presets:
  1. `cmake --preset tests-debug`
  2. `cmake --build --preset tests-debug`
  3. `ctest --preset tests-debug`
- Current repo preset generator is `MinGW Makefiles`, so non-Windows environments may require local preset adjustment before tests can run.

## Debugging Tips

- Use VS Code F5 with the provided launch config so PATH/runtime DLL handling is consistent.
- If keyboard input appears unresponsive, click the game window to restore focus.
- If `main.exe` fails to launch, verify runtime DLL availability (`runtime\` or toolchain/SFML `bin` on PATH).
- If fonts are missing, the game falls back to limited menu behavior via window-title prompts.

## Common Gotchas

- Running `g++` without SFML `-I` and `-L` flags causes missing-header/link errors.
- Double-clicking `main.exe` can fail if `runtime\` is not on PATH.
- Old DLL copies at repo root can mask runtime issues; prefer the managed `runtime\` path.
- CMake presets assume Windows MinGW generator by default.

## Coding Standards

- Language baseline: **C++20**.
- Keep gameplay constants centralized in shared headers (for example `GameConstants.h`) instead of hardcoding duplicates.
- Prefer small, testable helper/state logic (see `GameHelpers.*`, `GameManager.*`, `PhysicsManager.*`) for deterministic tests.
- Follow existing project naming/style in touched files; avoid mixing unrelated style changes into feature work.
- When changing behavior, update related documentation and test coverage in the same PR.

## Building & Releasing

- Build artifacts:
  - Windows: `main.exe` (root) + runtime DLLs under `runtime\`
  - macOS/Linux script target: `main`
- Release readiness checklist:
  1. Build succeeds with documented script/workflow.
  2. Manual gameplay sanity pass completed.
  3. Unit tests run (where environment supports current presets).
  4. Documentation and controls/setup notes are up to date.
- Current release process is manual; no CI release pipeline is defined in this repository yet.

## Overlap Review Candidates (Do Not Delete Yet)

The following sections overlap with this guide and should be reviewed for potential trimming or cross-linking:

- `README.md`
  - `## Setup Instructions (Windows)`
  - `## Build and Run`
  - `## Automated Tests`
  - `## Known Limitations` (development-environment/tooling portions)
- `docs/01_features/EPIC-1_Core_Gameplay/FS-10_Build_Setup_Tooling_and_Repository_Workflow.md`
  - Purpose/scope and requirement text describing setup, tooling, and build workflow details
- `docs/01_features/EPIC-1_Core_Gameplay/FS-11_Testing_and_Quality_Assurance.md`
  - Implementation/testing considerations that duplicate practical “how to run tests” guidance
- `docs/01_features/EPIC-1_Core_Gameplay/FS-12_User_Guide_Assets_and_Documentation_Support.md`
  - Setup/troubleshooting expectations overlapping developer environment instructions
- `docs/02_management/Phase1_Source_Summary.md`
  - `## Testing Approach` and environment-related points in `## Limitations`
