# Feature Specification Index
## CMSC 495 Capstone Project
## Project Title: The Breakout Game in C++

**Course:** CMSC 495 – Computer Science Capstone  
**Section:** 7381  
**Semester:** Spring 2026  
**Team Members:** Ethan Wasniak, Brendan Laird, Steven Dickinson, Kensie Balton, Francini Clemmons  
**Primary Communication Platform:** Discord  
**Version:** 0.1 Draft  
**Last Updated:** 2026-03-16

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

# 2. How to Use This Index

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

# 3. Feature Specification List

## FS-01: Game Window and Main Loop
**Document Name:** `FS-01_Game_Window_and_Main_Loop.md`  
**Category:** Core Architecture  
**Priority:** High  

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

# 4. Priority Tiers

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

# 5. Suggested Development Order

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

# 6. Open Decisions That May Affect Feature Specs

The following project decisions are still open and may affect implementation details across multiple Feature Specifications:

- final team role assignments
- selected C++ graphics/game library or framework
- target operating system and development environment
- degree of automation in testing
- whether stretch features will be attempted
- any team availability or skill constraints that may alter sequencing

These open decisions do not prevent drafting individual Feature Specifications, but they should be resolved as early as possible.

---

# 7. Next Steps

The next recommended actions are:

1. confirm the feature list as a team
2. draft the Tier 1 Feature Specifications first
3. identify owners for each Feature Specification
4. create the Task Board based on approved Feature Specs
5. document decisions about framework/tooling and team roles as they are finalized

---

# 8. Approval / Review

| Team Member | Reviewed | Notes |
|---|---|---|
| Ethan Wasniak | [Yes/No] | |
| Brendan Laird | [Yes/No] | |
| Steven Dickinson | [Yes/No] | |
| Kensie Balton | [Yes/No] | |
| Francini Clemmons | [Yes/No] | |