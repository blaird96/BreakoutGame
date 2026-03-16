# Master Project Blueprint
## CMSC 495 Capstone Project
## Project Title: The Breakout Game in C++

**Course:** CMSC 495 – Computer Science Capstone  
**Section:** 7381  
**Semester:** Spring 2026  
**Team Name:** [Insert Team Name]  
**Prepared By:** [Insert Team Member Names]  
**Version:** 0.1 Draft  
**Last Updated:** [Insert Date]

---

# 1. Executive Summary

This project will design, implement, test, and document a playable Breakout-style game written in C++. The system will provide a desktop game experience in which the player controls a paddle to bounce a ball, break bricks, accumulate points, and attempt to clear the board without losing all lives.

The project is intended to demonstrate the team’s ability to execute a full software development lifecycle within the time constraints of CMSC 495. The effort will include project planning, requirements analysis, software design, phased implementation, testing, documentation, and final reporting. In addition to producing a working game, the team will maintain organized documentation and version control practices so that the project can be clearly explained, evaluated, and extended.

This blueprint serves as the central planning and coordination artifact for the project. It establishes the project’s goals, scope, resources, team roles, communication process, milestones, risks, and evaluation approach. It is intended to guide the team’s work throughout the course and to support later course deliverables, including the Project Plan, Project Design, Test Plan, User Guide, and Final Report.

---

# 2. Project Overview

## 2.1 Project Description

The Breakout Game in C++ is a desktop-based arcade game inspired by the classic Breakout formula. The player controls a horizontal paddle that moves along the bottom of the screen. A ball bounces throughout the play area, destroying bricks on contact. The player must keep the ball in play, prevent it from falling below the paddle, and clear the brick layout to win.

The project will be implemented in C++ using an appropriate graphics/game development library selected by the team. The game will include core mechanics such as movement, collision detection, score tracking, life tracking, win/loss states, and a replay or restart workflow. Depending on time and complexity, optional enhancements may include sound effects, multiple levels, pause support, and visual polish.

## 2.2 Problem Statement

The project addresses the need to build a manageable but complete software application that demonstrates practical competency in software engineering, object-oriented programming, modular design, testing, collaboration, and documentation. A Breakout game is an appropriate capstone project because it is small enough to complete in an eight-week course but still contains meaningful design and implementation challenges, including real-time input handling, game state management, physics/collision logic, modular code organization, and user-facing behavior.

## 2.3 Project Justification

This project is suitable for CMSC 495 because it supports the course objective of researching, planning, conducting, and completing a collaborative computer-related project under schedule deadlines. It also provides a clear path for demonstrating analysis, design, development, implementation, testing, and documentation in a reusable and scalable software structure. :contentReference[oaicite:4]{index=4}

## 2.4 Intended Users

The intended users are:
- the project team, as developers and testers
- the instructor, as evaluator and reviewer
- basic end users who want to install and play a simple desktop arcade game

The project is not intended for commercial release or large-scale deployment. It is an academic software engineering deliverable designed to demonstrate sound development practices.

---

# 3. Project Goals and Objectives

## 3.1 Primary Goal

To successfully deliver a playable, tested, and documented Breakout-style game in C++ by the end of the CMSC 495 course.

## 3.2 Project Objectives

The team will pursue the following objectives:

1. Design and implement a functional Breakout game with modular C++ code.
2. Establish a clear software architecture and maintain organized project documentation.
3. Use version control and collaborative development practices to manage multi-person contributions.
4. Create and execute a structured test plan covering gameplay functionality, correctness, stability, and usability.
5. Produce user-facing and technical documentation that explains installation, operation, design, and testing.
6. Deliver all required course artifacts on schedule, with each artifact building logically on prior work.

## 3.3 Success Criteria

The project will be considered successful if the following conditions are met:

- The game compiles and runs successfully in the intended development environment.
- The player can move the paddle and keep the ball in play.
- Ball collisions with walls, paddle, and bricks behave correctly.
- Bricks are removed or updated appropriately when hit.
- Score and lives are tracked correctly.
- Win and loss conditions are implemented and displayed.
- Core features are tested and documented.
- The team submits all required deliverables with evidence of coordinated planning, implementation, testing, and documentation.

---

# 4. Project Scope

## 4.1 In-Scope Features

The following capabilities are included in the current project scope:

- C++ implementation of the Breakout game
- A graphical game window
- Main game loop and frame updates
- Keyboard-controlled paddle movement
- Ball movement and screen boundary handling
- Brick layout rendering and brick state changes
- Paddle, wall, and brick collision detection
- Score tracking
- Life tracking
- Win and loss conditions
- Restart or replay support
- Source code documentation
- Unit and/or functional test coverage for major game logic
- Basic user documentation
- Final technical and process documentation

## 4.2 Out-of-Scope Features

The following items are currently excluded unless time permits and the team formally approves them as stretch goals:

- Online multiplayer
- Networked leaderboards
- Mobile deployment
- Advanced 3D graphics
- Account management or user profiles
- Cloud storage or backend services
- Procedural level generation
- Full commercial-grade asset pipeline
- Cross-platform packaging beyond the team’s selected primary target environment

## 4.3 Scope Constraints

The project is constrained by:
- the limited duration of the CMSC 495 course
- the availability and skill sets of team members
- the need to balance functionality with documentation
- the need to select tools and libraries the team can realistically learn and support within the term

Because of these constraints, the team will prioritize a stable and well-documented core game over excessive optional features.

---

# 5. Functional and Non-Functional Requirements

## 5.1 Functional Requirements

The system shall:

- open and display a playable game window
- allow the player to move the paddle horizontally using keyboard input
- initialize the ball and update its motion continuously during gameplay
- detect collisions between the ball and screen boundaries
- detect collisions between the ball and the paddle
- detect collisions between the ball and bricks
- update brick state when bricks are hit
- update the player’s score when appropriate
- decrement lives when the ball is lost
- end the game when the player has no remaining lives
- recognize a win state when all required bricks are cleared
- allow the player to restart or begin a new session

## 5.2 Non-Functional Requirements

The system should:

- compile consistently in the selected C++ development environment
- use clear modular organization with logical separation of responsibilities
- remain readable and maintainable through comments and external documentation
- provide responsive gameplay controls
- behave reliably during ordinary play sessions without crashes
- support testing of critical gameplay logic
- be simple enough for a new user to install and run using the User Guide

---

# 6. Methodology

## 6.1 Development Approach

The project will follow a lightweight Agile-style methodology. This choice is appropriate because the course itself is phased and iterative, and because the project will likely require refinement as the team moves from design to implementation to testing. The team will work in short cycles, focusing on discrete features, reviewing progress regularly, and adjusting tasks as needed.

This methodology supports:
- incremental development
- rapid feedback
- manageable task assignment
- adaptation when technical issues emerge
- continuous documentation rather than last-minute reconstruction

## 6.2 Implementation Strategy

The implementation approach will be:

1. define project scope and core requirements
2. create high-level design and feature breakdown
3. establish development environment and repository structure
4. implement foundational features first
5. test each major subsystem as it is completed
6. integrate features incrementally
7. document decisions, changes, and results throughout the project lifecycle

## 6.3 Documentation Strategy

The team will maintain documentation continuously rather than treating it as a final-stage chore. Major project artifacts will include:
- the Master Project Blueprint
- feature specifications
- task board
- evidence log
- meeting notes
- decision log
- deliverable drafts

This is deliberate. The course rewards structured process, not just “look, it runs on my machine.” The syllabus and assignment sequence make that very clear. :contentReference[oaicite:5]{index=5} :contentReference[oaicite:6]{index=6}

---

# 7. Work Breakdown Structure

## 7.1 Major Workstreams

The project will be divided into the following major workstreams:

### Workstream 1: Planning and Coordination
- finalize team structure
- define scope and requirements
- create master planning documents
- manage schedule and risks
- coordinate submissions

### Workstream 2: Environment and Tooling
- choose graphics/game framework
- configure IDE and compiler settings
- establish repository structure
- set up version control workflow
- confirm build instructions

### Workstream 3: Core Game Architecture
- define classes and responsibilities
- create game loop
- define game states
- structure rendering and update logic

### Workstream 4: Gameplay Implementation
- paddle movement
- ball movement
- wall collision
- paddle collision
- brick system
- scoring and lives
- win/loss conditions
- restart flow

### Workstream 5: Testing and Quality Assurance
- identify testable components
- write test cases
- run manual and automated tests
- track and resolve defects
- validate gameplay behavior

### Workstream 6: Documentation and Delivery
- maintain evidence log
- prepare project plan
- prepare design document
- prepare test plan
- prepare user guide
- prepare final report
- prepare final presentation

## 7.2 Feature-to-Deliverable Mapping

Each major feature or subsystem should map to:
- a feature spec
- one or more tasks
- one or more test cases
- evidence in the evidence log
- at least one supporting section in a course deliverable where relevant

This traceability is intended to prevent confusion, duplication, and last-minute guesswork.

---

# 8. Project Deliverables

## 8.1 Internal Deliverables

The team will maintain the following internal documents:
- Master Project Blueprint
- Feature Specification Index
- individual Feature Specs
- Task Board
- Risk Register
- Decision Log
- Meeting Notes
- Evidence Log

## 8.2 Course Deliverables

The project will support the following course deliverables:
- Unit 2 Project Plan
- Unit 3 Project Design
- Unit 4 Phase I Source Code
- Unit 5 Test Plan
- Unit 6 Phase II Source Code
- Unit 7 User Guide
- Unit 8 Final Report
- Project Presentation

These deliverables reflect the course’s required sequence of planning, design, phased implementation, testing, user documentation, and final integrated reporting. :contentReference[oaicite:7]{index=7} :contentReference[oaicite:8]{index=8} :contentReference[oaicite:9]{index=9} :contentReference[oaicite:10]{index=10} :contentReference[oaicite:11]{index=11}

---

# 9. Project Resources

## 9.1 Personnel Resources

Project personnel will include the assigned team members in CMSC 495. Each member may hold more than one role due to the limited size of the team, which is consistent with the sample project plan provided in the course materials. :contentReference[oaicite:12]{index=12}

## 9.2 Software Resources

Planned software resources may include:
- C++ compiler
- IDE (e.g., Visual Studio, CLion, VS Code, or equivalent)
- graphics/game library selected by the team
- Git and GitHub or equivalent version control platform
- Markdown editor or word processor for documentation
- testing framework or manual test harness tools as needed

## 9.3 Hardware Resources

Planned hardware resources may include:
- personal computers capable of compiling and running C++ graphical applications
- internet access for repository collaboration and research
- local machines for testing the application in the intended target environment

## 9.4 Budget

The project is expected to operate with minimal or no direct financial cost. The team will prioritize free or student-accessible tools, libraries, and documentation platforms.

---

# 10. Team Roles and Responsibilities

Because of the limited project timeline and likely limited team size, team members may perform multiple roles. This follows the logic of the sample project plan, where members share responsibilities across management, coding, interface design, and related tasks. :contentReference[oaicite:13]{index=13}

## 10.1 Proposed Roles

### Project Coordinator
- tracks milestones and deadlines
- organizes meetings and follow-ups
- monitors completion of documents and submissions
- helps resolve workflow bottlenecks

### Lead Developer / Systems Integrator
- oversees overall code structure
- coordinates integration between modules
- monitors build stability and branch consistency

### Gameplay Developer
- implements core mechanics such as movement, collision, game state, and score logic

### UI / Visual Developer
- manages layout, HUD, menus, and visual presentation
- supports player-facing usability improvements

### Test and QA Lead
- organizes test cases and procedures
- tracks defects and retesting
- validates that features meet acceptance criteria

### Documentation Lead
- manages draft quality for deliverables
- ensures traceability between implementation and reports
- collects screenshots, diagrams, and evidence artifacts

## 10.2 Team Responsibility Matrix

| Area | Primary Owner | Secondary Owner | Notes |
|---|---|---|---|
| Project coordination | [Name] | [Name] | Tracks deadlines and submission readiness |
| Core architecture | [Name] | [Name] | Maintains class/module structure |
| Gameplay logic | [Name] | [Name] | Paddle, ball, brick, score, lives |
| UI / visuals | [Name] | [Name] | Menus, HUD, layout, polish |
| Testing | [Name] | [Name] | Test cases, execution, bug tracking |
| Documentation | [Name] | [Name] | Course deliverables and evidence |

---

# 11. Communication Plan

The course explicitly expects collaboration and communication planning as part of the Project Plan. :contentReference[oaicite:14]{index=14}

## 11.1 Communication Channels

The team will use the following channels:
- group chat platform: [Discord / GroupMe / Teams / other]
- version control platform comments/issues: [GitHub / other]
- video meetings: [Zoom / Teams / Google Meet]
- shared documents folder: [Google Drive / OneDrive / repo docs folder]

## 11.2 Meeting Frequency

The team will aim for:
- one scheduled group meeting per week
- one asynchronous check-in midweek
- additional ad hoc technical meetings when integration or debugging requires it

## 11.3 Expected Communication Standards

Team members are expected to:
- respond within a reasonable timeframe
- communicate blockers early
- update task status honestly
- record important decisions in writing
- avoid disappearing into the swamp and resurfacing on submission day with chaos

## 11.4 Escalation Path

If a project issue arises:
1. raise the issue in the group communication channel
2. discuss owner and next action
3. document the decision or change
4. notify the instructor if the issue materially affects scope, coordination, or submission quality

---

# 12. Schedule and Milestones

The sample project plan uses a milestone-oriented schedule and separates planning, coding, testing, and documentation. That structure fits this course well and should be adapted here. :contentReference[oaicite:15]{index=15}

## 12.1 High-Level Schedule

| Phase | Target Focus | Planned Outcome |
|---|---|---|
| Week 1 | Team formation and project selection | Confirm project topic and repo/document structure |
| Week 2 | Project planning | Submit Project Plan |
| Week 3 | Project design | Submit Project Design |
| Week 4 | Phase I implementation | Core architecture and initial gameplay components |
| Week 5 | Testing design | Submit Test Plan |
| Week 6 | Phase II implementation | Complete core functionality and refine code |
| Week 7 | User documentation | Submit User Guide |
| Week 8 | Final integration and reflection | Submit Final Report, final code, and presentation |

## 12.2 Internal Milestones

### Milestone 1: Planning Complete
- project blueprint drafted
- team roles assigned
- communication process established
- scope approved

### Milestone 2: Design Complete
- feature breakdown complete
- architecture defined
- major risks documented
- tasks estimated

### Milestone 3: Phase I Playable Foundation
- project builds successfully
- game window functional
- paddle and ball movement implemented
- at least partial collision behavior operational

### Milestone 4: Testing Framework Ready
- test cases documented
- defect tracking process established
- validation approach approved

### Milestone 5: Feature Completion
- brick logic complete
- scoring and lives complete
- win/loss flow complete
- restart/replay logic complete

### Milestone 6: Documentation Completion
- user guide drafted
- screenshots captured
- evidence log updated
- final report outline populated

### Milestone 7: Final Submission Readiness
- code reviewed
- tests rerun
- known issues documented
- final deliverables proofread and assembled

---

# 13. Risks and Mitigation

The sample project plan explicitly includes a risk section with probability, impact, and action. This project should do the same. :contentReference[oaicite:16]{index=16}

| Risk | Probability | Impact | Mitigation Strategy |
|---|---|---|---|
| Team scheduling conflicts | High | High | Use asynchronous updates, shared task board, and fixed weekly meeting time |
| Inexperience with chosen graphics library | Medium to High | High | Choose a manageable library early and build a minimal prototype immediately |
| Scope creep | High | High | Freeze core scope early; treat extra features as stretch goals only |
| Integration issues between modules | Medium | High | Use regular pull/merge reviews and integrate often rather than all at once |
| Weak version control practices | Medium | High | Define branch naming and merge expectations early |
| Incomplete testing | Medium | High | Build test cases from feature acceptance criteria throughout development |
| Documentation lag | High | High | Update docs continuously after each completed feature |
| Late bug discovery | Medium | Medium to High | Conduct recurring manual playtests and targeted subsystem tests |
| Uneven team contribution | Medium | High | Assign clear ownership and record task/evidence by contributor |
| Tooling/setup failures | Medium | Medium | Standardize compiler/library instructions and keep a working build guide |

---

# 14. Quality and Evaluation Plan

The Project Design assignment requires a clear evaluation plan, and the Test Plan later expands on that expectation. :contentReference[oaicite:17]{index=17} :contentReference[oaicite:18]{index=18}

## 14.1 Progress Evaluation

Project progress will be evaluated using:
- completion of milestone targets
- percentage of assigned tasks completed
- successful integration of major subsystems
- number and severity of unresolved defects
- readiness of course deliverables
- evidence log completeness

## 14.2 Product Evaluation

The finished product will be evaluated based on:
- correctness of core gameplay mechanics
- stability of the application during normal play
- code organization and maintainability
- quality and completeness of tests
- usability of the interface and controls
- completeness of documentation

## 14.3 Team Evaluation

Team performance will be evaluated based on:
- reliability of communication
- timely completion of assigned work
- participation in planning and review
- quality of collaboration during integration and testing
- ability to document contributions and decisions clearly

---

# 15. Testing Strategy Summary

A formal Test Plan will be developed later, but the project will begin with this high-level testing strategy.

## 15.1 Planned Testing Types

The team expects to use:
- unit testing for key logic modules where practical
- functional testing for gameplay features
- manual playtesting for usability and correctness
- regression testing after bug fixes
- integration testing as modules are combined

## 15.2 Core Test Targets

Core test targets include:
- paddle movement behavior
- ball movement updates
- wall bounce logic
- paddle collision logic
- brick collision and removal/update behavior
- scoring and lives calculations
- win/loss transitions
- restart/replay behavior

## 15.3 Defect Handling

Defects will be tracked in a shared list or issue board with:
- defect description
- severity
- owner
- date discovered
- resolution status
- retest result

This aligns with the course’s expectation that testing include objectives, scope, strategy, cases, procedures, schedule, resources, and defect management. :contentReference[oaicite:19]{index=19}

---

# 16. Documentation and Evidence Strategy

The final report rubric places heavy emphasis on integrated documentation, process description, test scripts, design choices, and team contributions. :contentReference[oaicite:20]{index=20}

## 16.1 Evidence to Capture Throughout the Project

The team should capture:
- screenshots of game states and UI changes
- diagrams of architecture or class relationships
- commit references for major milestones
- summaries of completed tasks
- test execution records
- notes on bugs found and fixes applied
- major design decisions and their rationale

## 16.2 Why This Matters

Maintaining evidence throughout development will make it easier to:
- write the User Guide
- describe design evolution
- explain test results
- show development history
- support the Final Report with specifics instead of vague fog and last-minute mythology

---

# 17. Assumptions and Constraints

## 17.1 Assumptions
- team members have access to computers capable of compiling and running C++ applications
- the team can agree on a shared toolchain early in the project
- the selected library/framework will be documented enough for successful implementation
- team members will contribute to both development and documentation at some level

## 17.2 Constraints
- limited course duration
- possible team availability conflicts
- varying levels of experience with graphics/game programming
- documentation and coding must proceed in parallel
- final project quality depends on maintaining schedule discipline

---

# 18. Change Management

Any significant change to project scope, architecture, tooling, or milestone priorities should be:
1. discussed by the team
2. documented in the decision log
3. reflected in the task board and schedule
4. incorporated into later deliverables where relevant

Scope changes should be justified based on feasibility, technical necessity, or course expectations rather than whim.

---

# 19. Immediate Next Steps

The team’s immediate next steps are:

1. finalize team member names and role assignments
2. confirm the selected graphics/game library and development environment
3. create the Feature Specification Index
4. draft the first feature specifications for core gameplay
5. establish the task board and evidence log
6. begin work on the Unit 2 Project Plan using this blueprint as the source document

---

# 20. Approval / Sign-Off

| Team Member | Role | Reviewed | Notes |
|---|---|---|---|
| [Name] | [Role] | [Yes/No] | |
| [Name] | [Role] | [Yes/No] | |
| [Name] | [Role] | [Yes/No] | |

---

# Appendix A: Suggested Initial Feature Spec List

- FS-01 Game Window and Main Loop
- FS-02 Paddle Input and Movement
- FS-03 Ball Motion and Boundary Collision
- FS-04 Brick Grid and Brick State
- FS-05 Ball-to-Paddle and Ball-to-Brick Collision
- FS-06 Score, Lives, and End States
- FS-07 Start Menu, Pause, and Restart
- FS-08 HUD, Audio, and Visual Feedback
- FS-09 Build Setup and Repository Workflow
- FS-10 Testing and QA Support
- FS-11 User Guide Assets and Screenshots

---

# Appendix B: Suggested Supporting Documents

- `/docs/00_master/Project_Blueprint.md`
- `/docs/00_master/Risk_Register.md`
- `/docs/00_master/Milestone_Schedule.md`
- `/docs/01_features/Feature_Spec_Index.md`
- `/docs/02_management/Task_Board.md`
- `/docs/02_management/Evidence_Log.md`
- `/docs/02_management/Decision_Log.md`
- `/docs/02_management/Meeting_Notes.md`