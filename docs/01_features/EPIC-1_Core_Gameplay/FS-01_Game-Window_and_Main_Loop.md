# FS-01: Game Window and Main Loop

**Category:** Core Architecture  
**Priority:** High  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Partial |
| **Primary evidence** | [`main.cpp`](../../main.cpp) lines 4, 17–24, 24, 61–62 |
| **Gaps** | No fixed timestep or delta-time abstraction; no dedicated resource init/shutdown layer; gameplay entities created inline in `main` |

### 2026-04-09 Addendum

- **Updated implementation status:** Mostly complete (~85%)
- **Current evidence:** `phase1_main.cpp`, `Game.cpp` (`Game::run`, `initialize`, `handleEvents`, `render`)
- **Complete now:** Dedicated `Game` class lifecycle, window creation/close handling, dt-based frame update, clear/draw/display sequencing.
- **Partially complete:** Some responsibilities still centralized in `Game.cpp`; no explicit shutdown/resource service layer.
- **Outstanding:** Further modularization into smaller subsystems and improved architecture-level documentation.

---

## Purpose and scope

**Owns:** Application window lifecycle, primary loop ordering (events → simulation draw prep → present), and baseline rendering of the cleared framebuffer.

**Out of scope:** Paddle/ball/brick rules (FS-02–FS-05), score and lives logic beyond what the loop invokes (FS-06), menus (FS-07), HUD text (FS-08), audio (FS-09).

---

## Definitions

- **Frame:** One iteration of the main loop: process events, clear, draw scene, `display`.
- **Playfield outline:** Visual border segments; in the prototype, line primitives at x = 10 / 790 and y = 10 / 790 (`main.cpp` 26–32).

---

## Data model and attributes

Prototype-level constants (current code):

| Attribute | Value | Location |
| --- | --- | --- |
| `window_width` | 800 | `sf::VideoMode({800, 850})` |
| `window_height` | 850 | same |
| `window_title` | `"Breakout Game"` | `RenderWindow` constructor |
| `clear_color` | RGB (0, 0, 0) | `window.clear` |
| Wall inset (visual) | 10 px from window edges | border vertices |

---

## Functional requirements

1. **FS-01.1** The system SHALL create an SFML `RenderWindow` with defined width, height, and title before entering the main loop.
2. **FS-01.2** The system SHALL run while the window is open, processing window events each frame.
3. **FS-01.3** The system SHALL clear the window to a defined background color at the start of each frame’s draw pass.
4. **FS-01.4** The system SHALL present drawn content to the screen each frame (`display`).
5. **FS-01.5** The system SHALL close the application cleanly when the user closes the window (`Closed` event).
6. **FS-01.6** (Target) The system SHOULD separate initialization and shutdown into dedicated functions or types for maintainability.

*Traceability:* Project_Blueprint functional requirement “open and display a playable game window” — satisfied by current loop; polish and structure are incremental.

---

## Non-functional requirements

- **NFR-01** The loop SHALL remain responsive to OS window events (close) without blocking on gameplay logic in the prototype path.
- **NFR-02** (Target) Frame pacing SHOULD use elapsed time or SFML clock if gameplay becomes frame-rate dependent elsewhere (see FS-02 speed note).

---

## Dependencies

- **Requires:** FS-10 (SFML available, project builds).
- **Enables:** FS-02, FS-03 (entities drawn inside this loop).

---

## Interfaces and events

**Inputs**

- OS/window: `sf::Event::Closed` → close window.

**Outputs**

- Cleared and presented framebuffer each frame.
- (Implicit) subsequent FS subsystems draw into the same `RenderWindow`.

**Procedural API (as-built):** all logic inline in `main()`; no `Game` class yet.

---

## Acceptance criteria

- [ ] Launching the built executable opens an 800×850 titled window.
- [ ] Window shows a black clear color and subsequent draws (paddle, ball, borders).
- [ ] Closing the window exits the process without hang or crash.
- [ ] (Target) README or build script documents how any teammate configures SFML paths for the same entry target.

**Definition of done (Tier 1):** Stable window and loop on agreed team OS/toolchain; loop order documented; no known resource leak on exit.

---

## Implementation notes

**As-built:** Single `while (window.isOpen())` loop with inner `pollEvent` handling, then `clear`, draw calls for borders/paddle/ball, then `display` (`main.cpp` 17–62).

**Target:** Extract `initializeWindow()`, `processEvents()`, `render()`; optional fixed timestep update phase between events and render.

---

## Testing considerations

- Manual: open/close window repeatedly; verify exit code 0.
- Manual: resize behavior (if resize allowed in future; currently not specified).
- Future: smoke test executable launch in CI if build becomes path-portable.

---

## Documentation and evidence

- Screenshot: running window with title bar visible.
- Final report: short paragraph naming SFML version and loop order.

---

## Open questions and decisions

- Whether to allow window resizing and how playfield scales.
- Whether to introduce `sf::Clock` for delta time globally in FS-01 vs. FS-02/FS-03 only.
