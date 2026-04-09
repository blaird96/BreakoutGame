# FS-08: HUD, Visual Feedback, and Presentation

**Category:** User Interface  
**Priority:** Medium  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Not started (for HUD text/overlays) |
| **Primary evidence** | [`main.cpp`](../../main.cpp) draws border lines, paddle, and ball only (lines 26–32, 43, 59) |
| **Gaps** | No `sf::Text` for score/lives; no win/loss overlays; no font loading; optional particle/flash feedback |

### 2026-04-09 Addendum

- **Updated implementation status:** Mostly complete (~88%)
- **Current evidence:** `Game.cpp` (`updateHudText`, menu/status rendering, font loading fallback), `README.md` control and fallback notes
- **Complete now:** Score and lives HUD, win/game-over overlays, menu and settings UI text, fallback behavior when no project font is present.
- **Partially complete:** Enhanced visual feedback effects (brick impact flashes/particles) and formal accessibility pass are still limited.
- **Outstanding:** Add optional feedback polish, finalize font packaging guidance, and capture evidence screenshots for documentation deliverables.

---

## Purpose and scope

**Owns:** On-screen information design: score, lives, instructional hints, win/loss banners; optional subtle feedback when bricks break or lives are lost.

**Out of scope:** Core simulation (FS-03–FS-06); audio (FS-09); main menu layout beyond shared text styling (coordinate with FS-07).

---

## Definitions

- **HUD:** Heads-up display — typically top strip or corners for score/lives.
- **Presentation polish:** Readable fonts, contrast against background, spacing.

---

## Data model and attributes (target)

| Element | Description |
| --- | --- |
| `font` | `sf::Font`, loaded from file bundled in repo or OS path — **TBD** |
| `scoreText`, `livesText` | `sf::Text` |
| `messageText` | Win / loss / pause overlay |
| `hudPosition`, `fontSize` | Layout constants |
| Colors | High contrast on black clear color |

---

## Functional requirements

1. **FS-08.1** The system SHALL display the current score during play once scoring exists (FS-06).
2. **FS-08.2** The system SHALL display remaining lives during play.
3. **FS-08.3** The system SHALL display an obvious message or scene distinction for win and game-over states (FS-06/07).
4. **FS-08.4** The system SHOULD use legible font size and color for 800×850 window at intended viewing distance.
5. **FS-08.5** (Optional) Brief visual feedback MAY occur on brick destruction or life lost.

---

## Non-functional requirements

- **NFR-01** HUD updates SHALL not drop frame rate below playable on target hardware for typical brick counts.
- **NFR-02** Text SHOULD remain readable for color-blind players (avoid red-on-green only distinctions).

---

## Dependencies

- **Requires:** FS-06 data; FS-07 for which message to show; FS-01 render target.
- **Asset:** Font file or bundled default path documented in FS-12.

---

## Interfaces and events

**Inputs:** Read-only view of `score`, `lives`, `GameState`.

**Outputs:** Draw calls issued each frame or only on state change for overlays.

---

## Acceptance criteria

- [ ] Player can read score and lives without pausing.
- [ ] Win and game-over states show clear messaging before restart (FS-07).
- [ ] Font loading failure is handled or documented (installer must include font).

---

## Implementation notes

**As-built:** Primitive line borders only; black background (`main.cpp` 24–32).

**Target:** Load font in initialization; `draw` HUD after playfield or before depending on layering; consider `sf::View` if camera added later.

---

## Testing considerations

- Manual: longest plausible score digit width still fits.
- Manual: verify HUD updates same frame as brick breaks.

---

## Documentation and evidence

- Screenshots annotated in User Guide.
- Accessibility note: font choice and size.

---

## Open questions and decisions

- Monospace vs. proportional font; open-source font licensing.
- Localized strings — likely English only for capstone.
