# FS-04: Brick Grid and Brick State

**Category:** Core Gameplay  
**Priority:** High  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Not started |
| **Primary evidence** | None in [`main.cpp`](../../main.cpp) |
| **Gaps** | Entire subsystem: data structure, layout, rendering, hit response, win condition support |

### 2026-04-09 Addendum

- **Updated implementation status:** Partially complete (~65%)
- **Current evidence:** `Game.h` (`Brick` struct), `Game.cpp` (`initializeBricks`, `resetBricks`, `renderBricks`)
- **Complete now:** Brick grid initialization (5x8), rendering of active bricks, active/inactive state handling, reset of grid for new rounds.
- **Partially complete:** Brick model is embedded in `Game` rather than a dedicated subsystem; no multi-hit brick/state variants.
- **Outstanding:** Extract brick subsystem into reusable module, add richer brick-state extensibility, and keep grid/state APIs aligned with future level support.

---

## Purpose and scope

**Owns:** Logical grid of bricks, per-brick state (active, optionally HP/color), spawning for a round, rendering, and queries for collision (with FS-05) and win detection (FS-06).

**Out of scope:** Ball integration details (FS-03), paddle (FS-02), scoring policy values unless stored here (FS-06 may own score integer).

---

## Definitions

- **Brick cell:** One destructible target aligned to grid indices `(row, col)`.
- **Grid:** Rectangular arrangement; dimensions TBD by team.

---

## Data model and attributes (target — not yet in code)

| Entity / attribute | Description |
| --- | --- |
| `Brick.row`, `Brick.col` | Grid indices |
| `Brick.bounds` | `sf::FloatRect` or position + size |
| `Brick.active` | `bool` or HP > 0 |
| `Brick.hp` | Optional hits to destroy (1 for classic) |
| `Brick.color` | Fill color per row or type |
| `GridConfig.rows`, `GridConfig.cols` | e.g. 5×10 — **open** |
| `GridConfig.margin`, `GridConfig.spacing` | Offset from playfield walls |
| `BrickGrid` container | `std::vector<Brick>` or 2D array |

Units: pixels, consistent with window 800×850 and wall inset ~10.

---

## Functional requirements

1. **FS-04.1** The system SHALL initialize a full grid of bricks at round start with defined rows, columns, spacing, and colors.
2. **FS-04.2** The system SHALL render only active bricks each frame.
3. **FS-04.3** The system SHALL expose a way to mark a brick inactive or reduce HP when the ball hits it (called from FS-05).
4. **FS-04.4** The system SHALL support resetting the grid for a new game or level (with FS-07).
5. **FS-04.5** The system SHALL allow FS-06 to query whether any active bricks remain (win detection).

---

## Non-functional requirements

- **NFR-01** Brick iteration per frame SHOULD be O(n) in brick count with n typical for Breakout (acceptable on target PC).
- **NFR-02** Layout SHOULD remain readable at 800×850 (brick size not too small).

---

## Dependencies

- **Requires:** FS-01 rendering context.
- **Blocks:** FS-05 brick collisions; FS-06 win state; FS-08 score tied to brick clears.

---

## Interfaces and events (target)

**Suggested API**

- `void resetBricks(const GridConfig& cfg);`
- `void drawBricks(sf::RenderWindow& window);`
- `bool hitBrickAt(const sf::FloatRect& ballBounds, /* out */ BrickId& id);` or circle overlap variant
- `bool anyBricksRemain() const;`

---

## Acceptance criteria

- [ ] New game shows a stable grid of bricks filling the upper playfield.
- [ ] Striking a brick removes it or decrements HP per design.
- [ ] Clearing all bricks triggers win path in FS-06 when integrated.
- [ ] Restart restores a full grid.

---

## Implementation notes

**As-built:** No bricks.

**Target:** Start with `std::vector<sf::RectangleShape>` or separate model + view; avoid magic numbers duplicated from wall bounds (share constants with FS-01/FS-03).

---

## Testing considerations

- Manual: clear one row at a time; verify no ghost collisions.
- Unit: `anyBricksRemain` after scripted hits; grid reset idempotent.
- Regression: ball never stuck inside brick after hit (FS-05 integration).

---

## Documentation and evidence

- Screenshot: full brick grid at game start.
- Blueprint trace: “brick layout rendering and brick state changes.”

---

## Open questions and decisions

- Rows/columns, colors, and whether multi-hit bricks are in scope.
- Brick placement relative to side walls (align with FS-03 bounce thresholds after cleanup).
