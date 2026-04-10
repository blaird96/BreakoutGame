# Feature Specification Index
## CMSC 495 Capstone Project
## Project Title: The Breakout Game in C++

**Course:** CMSC 495 – Computer Science Capstone  
**Section:** 7381  
**Semester:** Spring 2026  
**Team Members:** Ethan Wasniak, Brendan Laird, Steven Dickinson, Kensie Balton, Francini Clemmons  
**Primary Communication Platform:** Discord  
**Version:** 0.2  
**Last Updated:** 2026-04-01  

---

# 1. Purpose

This document provides the master index of Feature Specifications for the Breakout Game in C++ project. Each Feature Specification defines a major subsystem, capability, or supporting workstream required to plan, implement, test, document, and deliver the project successfully.

The purpose of this index is to:
- organize the project into manageable functional areas
- establish traceability between project requirements and implementation work
- support task generation and assignment
- ensure features are aligned with testing and documentation needs
- provide a clear roadmap for phased development and course deliverables

This index is intended to support the full project lifecycle, including planning, design, implementation, testing, documentation, and final reporting.

---

# 2. Implementation status summary

Status reflects the **current repository** as of **2026-04-01**: a single-file SFML prototype in `main.cpp` at the repository root, plus `README.md` and `.vscode/tasks.json` for build guidance.

- **FS-01** Game window and main loop — **Partial**
- **FS-02** Paddle input and movement — **Partial**
- **FS-03** Ball motion and boundary collision — **Partial**
- **FS-04** Brick grid and brick state — **Not started**
- **FS-05** Collision system (paddle and bricks) — **Partial** (paddle only in code)
- **FS-06** Score, lives, and end states — **Partial**
- **FS-07** Start menu, restart, game flow — **Not started**
- **FS-08** HUD, visual feedback, presentation — **Not started**
- **FS-09** Audio and optional enhancements — **Not started**
- **FS-10** Build setup, tooling, repository workflow — **Partial**
- **FS-11** Testing and quality assurance — **Not started** (no automated tests in repo)
- **FS-12** User guide assets and documentation support — **Partial**

**Traceability (FS → primary artifact):**

- **FS-01, FS-02, FS-03, FS-05 (paddle only), FS-06 (lives decrement only):** [`main.cpp`](../../main.cpp) — window/event loop (lines 4–62), paddle (5–7, 34–43), ball and walls/paddle bounce (9–13, 45–58), lives on miss (15, 54–58).
- **FS-04, FS-05 (brick collisions):** not implemented; no dedicated source files yet.
- **FS-07, FS-08:** not implemented in `main.cpp` (no game-state UI or menu layer).
- **FS-09:** not implemented (graphics link set only; no `sfml-audio`).
- **FS-10:** [`README.md`](../../README.md), [`.vscode/tasks.json`](../../.vscode/tasks.json).
- **FS-11:** specification only; no `tests/` or test harness in repository.
- **FS-12:** partial — setup and controls documented in `README.md`; screenshot and evidence checklist lives in FS-12 doc.

Individual Feature Specification documents contain detailed **Status**, requirements, attributes, and acceptance criteria aligned with this summary.

## 2A. 2026-04-09 status refresh addendum

The repository has materially advanced beyond the 2026-04-01 snapshot above. Current Phase I runtime is driven by `phase1_main.cpp` and `Game.cpp`, with gameplay constants in `GameConstants.h`, helper logic in `GameHelpers.h`, and helper/state unit tests under `tests/`.

- **FS-01** Game window and main loop — **Mostly complete** (~85%)
- **FS-02** Paddle input and movement — **Mostly complete** (~75%)
- **FS-03** Ball motion and boundary collision — **Partially complete** (~70%)
- **FS-04** Brick grid and brick state — **Partially complete** (~65%)
- **FS-05** Collision system (paddle and bricks) — **Mostly complete** (~80%)
- **FS-06** Score, lives, and end states — **Mostly complete** (~90%)
- **FS-07** Start menu, restart, game flow — **Mostly complete** (~85%)
- **FS-08** HUD, visual feedback, presentation — **Mostly complete** (~88%)
- **FS-09** Audio and optional enhancements — **Early/partial** (~20%)
- **FS-10** Build setup, tooling, repository workflow — **Partially complete** (~70%)
- **FS-11** Testing and quality assurance — **Partially complete** (~60%)
- **FS-12** User guide assets and documentation support — **Partially complete** (~50%)

Remaining legacy status lines in older sections are retained for historical traceability; the 2026-04-09 values above are the current baseline for planning and tasking.

---

# 3. How to Use This Index

Each item in this index should correspond to an individual Feature Specification document stored in the `/docs/01_features/` directory.

Each Feature Specification should include:
- feature purpose
- functional description
- requirements
- dependencies
- acceptance criteria
- implementation notes
- testing considerations
- documentation/evidence needs
- assigned owner(s)

Once approved, each Feature Specification should be broken down into implementation tasks and tracked in the project Task Board.

---

# 4. Feature Specification List

## FS-01: Game Window and Main Loop
**Document Name:** `FS-01_Game-Window_and_Main_Loop.md`  
**Category:** Core Architecture  
**Priority:** High  
**Implementation status (2026-04-01):** Partial  

### Summary
Defines the foundational runtime structure of the game, including creation of the application window, initialization of resources, the primary game loop, frame updates, rendering flow, and game shutdown behavior.

### Why It Matters
Without this feature, there is no running game. This is the spine of the whole system, not optional decorative nonsense.

### Likely Contents
- window creation
- initialization logic
- update/render loop
- frame timing
- input polling entry point
- shutdown/cleanup behavior

---

## FS-02: Paddle Input and Movement
**Document Name:** `FS-02_Paddle_Input_and_Movement.md`  
**Category:** Core Gameplay  
**Priority:** High  
**Implementation status (2026-04-01):** Partial  

### Summary
Defines how the player controls the paddle, including keyboard input handling, movement boundaries, responsiveness, and any related movement constraints.

### Why It Matters
The paddle is the player’s primary means of interacting with the game. If it feels bad, the whole project feels bad.

### Likely Contents
- keyboard input mapping
- paddle movement logic
- movement speed
- left/right screen limits
- responsiveness requirements

---

## FS-03: Ball Motion and Boundary Collision
**Document Name:** `FS-03_Ball_Motion_and_Boundary_Collision.md`  
**Category:** Core Gameplay  
**Priority:** High  
**Implementation status (2026-04-01):** Partial  

### Summary
Defines ball behavior, including initialization, directional movement, speed handling, and collision with the play area boundaries such as walls and ceiling.

### Why It Matters
The ball is the engine of gameplay. No ball logic, no Breakout — just a lonely rectangle drifting in existential silence.

### Likely Contents
- ball spawn/reset behavior
- movement update logic
- velocity and direction handling
- wall/ceiling collision
- loss condition trigger when ball leaves play area

---

## FS-04: Brick Grid and Brick State
**Document Name:** `FS-04_Brick_Grid_and_Brick_State.md`  
**Category:** Core Gameplay  
**Priority:** High  
**Implementation status (2026-04-01):** Not started  

### Summary
Defines how bricks are created, arranged, rendered, stored, and updated when struck by the ball.

### Why It Matters
Bricks are the target objects that define progression, scoring, and victory conditions.

### Likely Contents
- brick layout structure
- brick rendering
- active/inactive state
- brick durability assumptions, if any
- reset behavior for a new round

---

## FS-05: Ball-to-Paddle and Ball-to-Brick Collision
**Document Name:** `FS-05_Collision_System.md`  
**Category:** Core Gameplay  
**Priority:** High  
**Implementation status (2026-04-01):** Partial (paddle only)  

### Summary
Defines collision detection and response logic between the ball and interactive gameplay objects, especially the paddle and bricks.

### Why It Matters
Collision is where the game either feels coherent or reveals itself as a cardboard fraud.

### Likely Contents
- collision detection logic
- bounce direction rules
- interaction with paddle
- interaction with bricks
- object state updates after impact

---

## FS-06: Score, Lives, and End States
**Document Name:** `FS-06_Score_Lives_and_End_States.md`  
**Category:** Game State Management  
**Priority:** High  
**Implementation status (2026-04-01):** Partial  

### Summary
Defines the systems that track score, remaining lives, win condition, loss condition, and transitions between active play and end states.

### Why It Matters
Without game-state tracking, the game has motion but no consequence.

### Likely Contents
- score updates
- life decrement rules
- win detection
- loss detection
- game over / victory display states

---

## FS-07: Start Menu, Restart, and Game Flow Control
**Document Name:** `FS-07_Start_Menu_Restart_and_Game_Flow.md`  
**Category:** User Experience / Game State  
**Priority:** Medium to High  
**Implementation status (2026-04-01):** Not started  

### Summary
Defines how a session begins, how the player restarts after winning or losing, and how major gameplay states transition.

### Why It Matters
A project that only works once per launch is less a game and more a hostage situation.

### Likely Contents
- start screen/menu
- begin game action
- restart flow
- replay support
- state transitions between menu, play, win, and loss

---

## FS-08: HUD, Visual Feedback, and Presentation
**Document Name:** `FS-08_HUD_Visual_Feedback_and_Presentation.md`  
**Category:** User Interface  
**Priority:** Medium  
**Implementation status (2026-04-01):** Not started  

### Summary
Defines visual information presented to the player, such as score, lives, status messages, and basic presentation polish.

### Why It Matters
Even simple games need readable feedback so the user can understand what is happening.

### Likely Contents
- score display
- lives display
- win/loss messages
- simple visual status cues
- readability considerations

---

## FS-09: Audio and Optional Enhancement Support
**Document Name:** `FS-09_Audio_and_Optional_Enhancements.md`  
**Category:** Stretch / Enhancement  
**Priority:** Low to Medium  
**Implementation status (2026-04-01):** Not started  

### Summary
Defines optional enhancements such as sound effects, music, multiple levels, pause support, or other secondary improvements if time permits.

### Why It Matters
This feature allows the team to isolate stretch goals so they do not contaminate the core scope and derail the project.

### Likely Contents
- sound effects
- background audio
- pause support
- multiple levels
- visual polish beyond minimum functionality

---

## FS-10: Build Setup, Tooling, and Repository Workflow
**Document Name:** `FS-10_Build_Setup_Tooling_and_Repository_Workflow.md`  
**Category:** Engineering Support  
**Priority:** High  
**Implementation status (2026-04-01):** Partial  

### Summary
Defines the development environment, compiler assumptions, dependency setup, folder structure, repository conventions, and team workflow expectations.

### Why It Matters
If the code cannot be built consistently across the team, the project turns into ritual sacrifice by compiler.

### Likely Contents
- compiler/toolchain assumptions
- library/framework setup
- repository structure
- branch workflow
- build/run instructions
- version control conventions

---

## FS-11: Testing and Quality Assurance
**Document Name:** `FS-11_Testing_and_Quality_Assurance.md`  
**Category:** Quality Assurance  
**Priority:** High  
**Implementation status (2026-04-01):** Not started (strategy doc only; no test harness in repo)  

### Summary
Defines the testing strategy for the project, including testable components, manual and automated testing approaches, validation criteria, and defect handling.

### Why It Matters
The course expects explicit testing strategy and evidence, not vague claims that the game “seems fine on my machine.”

### Likely Contents
- testing scope
- feature-level test targets
- manual playtesting strategy
- unit/functional test opportunities
- defect tracking process
- regression testing approach

---

## FS-12: User Guide Assets and Documentation Support
**Document Name:** `FS-12_User_Guide_Assets_and_Documentation_Support.md`  
**Category:** Documentation Support  
**Priority:** Medium  
**Implementation status (2026-04-01):** Partial  

### Summary
Defines the assets, screenshots, instructions, and explanatory materials that must be captured during development to support the final User Guide and Final Report.

### Why It Matters
If this is ignored until the end, the team will wind up faking history from memory, which is always uglier than doing it right the first time.

### Likely Contents
- screenshot checklist
- setup instructions
- control instructions
- troubleshooting notes
- installation assumptions
- evidence needed for final report sections

---

# 5. Priority Tiers

## Tier 1: Core Must-Have Features
These features are required for the game to function and for the course deliverables to remain credible:
- FS-01 Game Window and Main Loop
- FS-02 Paddle Input and Movement
- FS-03 Ball Motion and Boundary Collision
- FS-04 Brick Grid and Brick State
- FS-05 Collision System
- FS-06 Score, Lives, and End States
- FS-10 Build Setup, Tooling, and Repository Workflow
- FS-11 Testing and Quality Assurance

## Tier 2: Important Supporting Features
These features improve usability, project completeness, and documentation quality:
- FS-07 Start Menu, Restart, and Game Flow Control
- FS-08 HUD, Visual Feedback, and Presentation
- FS-12 User Guide Assets and Documentation Support

## Tier 3: Stretch Features
These should only be pursued if Tier 1 and Tier 2 are stable:
- FS-09 Audio and Optional Enhancements

---

# 6. Suggested Development Order

The recommended implementation sequence is:

1. FS-10 Build Setup, Tooling, and Repository Workflow  
2. FS-01 Game Window and Main Loop  
3. FS-02 Paddle Input and Movement  
4. FS-03 Ball Motion and Boundary Collision  
5. FS-04 Brick Grid and Brick State  
6. FS-05 Collision System  
7. FS-06 Score, Lives, and End States  
8. FS-07 Start Menu, Restart, and Game Flow Control  
9. FS-08 HUD, Visual Feedback, and Presentation  
10. FS-11 Testing and Quality Assurance  
11. FS-12 User Guide Assets and Documentation Support  
12. FS-09 Audio and Optional Enhancements  

This order reflects the logic of building a stable playable foundation first, then completing state management, then polishing, then layering in stretch work if time remains.

---

# 7. Resolved and remaining open decisions

**Resolved (documented in repository as of 2026-04-01):**

- **Graphics / windowing library:** SFML 3.0.2 (`sfml-graphics`, `sfml-window`, `sfml-system`); see `README.md` and `main.cpp`.
- **Primary build target:** Windows, MinGW-w64 **32-bit** toolchain (`g++` 14.2.0 per README), SFML installed under `C:\SFML-3.0.2`, compiler under `C:\mingw32` as described in `README.md` and `.vscode/tasks.json`.
- **Testing approach for the current increment:** manual playtesting of `main.cpp` build; **automated tests not yet present** — FS-11 defines future scope (unit tests for collision/bricks, optional CI).

**Still open (team should record in Decision Log when finalized):**

- final team role assignments and owners per Feature Specification
- branch workflow and review rules (Task Board is empty as of this update)
- whether stretch goals (FS-09) will be in scope for the term
- brick grid dimensions, scoring rules, and tuning constants once FS-04/FS-06 are implemented
- path-portable build (e.g. CMake) vs. documented absolute paths on `C:\`

---

# 8. Next Steps

The next recommended actions are:

1. Use expanded Feature Specifications (FS-01 … FS-12) for task breakdown and assignment.
2. Populate `docs/02_management/Task_Board.md` from acceptance criteria in each FS (create the file and folder if the team adopts that layout from the Project Blueprint).
3. Implement missing Tier 1 items (especially FS-04, FS-06 completion, FS-05 brick collisions) before heavy Tier 2 polish.
4. Capture evidence per FS-12 as features land (screenshots, short clips, setup notes).
5. Record toolchain and process decisions team policy document (e.g. `docs/02_management/Decision_Log.md` per Project Blueprint) as they are finalized.

---

# 9. Approval / Review

| Team Member | Reviewed | Notes |
|---|---|---|
| Ethan Wasniak | [Yes/No] | |
| Brendan Laird | [Yes/No] | |
| Steven Dickinson | [Yes/No] | |
| Kensie Balton | [Yes/No] | |
| Francini Clemmons | [Yes/No] | |
