# FS-05: Ball-to-Paddle and Ball-to-Brick Collision

**Category:** Core Gameplay  
**Priority:** High  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Partial (paddle only) |
| **Primary evidence** | [`main.cpp`](../../main.cpp) lines 46–52 (paddle); no brick logic |
| **Gaps** | Brick-ball tests; robust normal/penetration handling; corner cases (ball inside paddle, tunneling at high speed) |

### 2026-04-09 Addendum

- **Updated implementation status:** Mostly complete (~80%)
- **Current evidence:** `Game.cpp` (`update`, `handleBrickCollisions`, paddle-angle bounce code)
- **Complete now:** Paddle collision with angle-based response, active brick collision detection, single-brick-per-frame deactivation, score trigger on brick hit.
- **Partially complete:** Brick response uses simplified reflection and overlap checks; limited penetration/tunneling handling.
- **Outstanding:** Improve side-aware collision normal resolution, add stronger overlap correction, and verify deterministic multi-contact behavior.

### 2026-04-19 Addendum

- **Updated implementation status:** Complete for Phase I collision goals (~95%)
- **Current evidence:** `Game.cpp` (`update`, wall clamp, `handleBrickCollisions`, paddle AABB + descending-velocity guard + English); [`src/Collision2D.h`](../../../src/Collision2D.h) (circle–AABB intersect, separation, axis reflection); [`tests/Collision2DTests.cpp`](../../../tests/Collision2DTests.cpp)
- **Complete now:** Left/right/top wall reflection with center clamp to legal inset bounds; brick hits use circle–AABB resolution with **side-aware** `reflectX` / `reflectY`, separation epsilon, and a **bounded multi-hit loop** per frame; paddle uses **full AABB** from center + size, requires **downward ball velocity** before accepting a hit, then separation + English.
- **Partially complete:** Order of resolution is walls → bricks → paddle (documented tradeoff for simultaneous paddle–brick contacts at high speed).
- **Outstanding:** Optional swept tests for extreme speed × `dt`; optional shared collision use from legacy `src/main.cpp` prototype.

---

## Purpose and scope

**Owns:** Detecting contact between the ball and interactive solids (paddle, bricks) and applying velocity response + state updates (e.g. brick inactive).

**Out of scope:** Wall/ceiling-only reflection (documented under FS-03 though paddle band overlaps conceptually), UI feedback (FS-08), audio (FS-09).

---

## Definitions

- **Paddle collision (prototype):** If `ball.y >= 780` and ball x strictly between `paddle.x - 75` and `paddle.x + 75`, flip `velocity.y`.
- **Circle–AABB / brick:** Target behavior — test circle against brick rectangle; choose reflection normal or destroy brick.

---

## Data model and attributes

| Item | Prototype behavior | Target |
| --- | --- | --- |
| Ball hit shape | Implicit center + radius 14 | Explicit `sf::CircleShape` or `FloatRect` bounds |
| Paddle hit shape | Horizontal segment implied by paddle half-width 75 | Full AABB 150×20 with normal |
| Brick hit shape | N/A | Per-brick rectangle from FS-04 |

---

## Functional requirements

1. **FS-05.1** The system SHALL detect collision between the ball and the paddle during play and update ball velocity so play continues (bounce).
2. **FS-05.2** The system SHALL detect collision between the ball and each active brick and update brick state per FS-04.
3. **FS-05.3** The system SHALL avoid double-counting the same brick hit in a single frame where practical (debounce or separation).
4. **FS-05.4** (Target) Bounce direction MAY vary by hit position on the paddle (English / angle tweak) for better feel.
5. **FS-05.5** (Target) Collision resolution SHOULD separate overlapping shapes to prevent jitter.

---

## Non-functional requirements

- **NFR-01** Collision pass SHOULD complete within one frame budget for expected brick counts.
- **NFR-02** Behavior SHOULD feel fair in manual playtests (no “random” phase through paddle).

---

## Dependencies

- **Requires:** FS-03 ball state; FS-02 paddle position; FS-04 active bricks for full scope.
- **Informs:** FS-06 (score on brick break).

---

## Interfaces and events

**Inputs:** Ball position/radius, velocity; paddle bounds; iterable active bricks.

**Outputs:** Mutated `velocity`; callbacks or direct mutation to bricks; possible score event to FS-06.

**As-built:** Phase I uses `Collision2D` helpers from `Game::update` / `Game::handleBrickCollisions` (see repository root `Game.cpp`).

---

## Acceptance criteria

- [ ] Ball bounces off paddle when intersecting from above in normal play.
- [ ] Ball destroys or marks hit when intersecting a brick (once FS-04 exists).
- [ ] No permanent stuck state in corner tests (paddle + wall).
- [ ] (Target) Documented rule for simultaneous brick + wall contact order.

---

## Implementation notes

**As-built:** Simple y-threshold and x-interval test; vertical velocity flip only (`main.cpp` 49–52). No restitution or tangent change.

**Target:** Consider splitting `resolvePaddleCollision` / `resolveBrickCollisions`; optional sweep for fast ball.

---

## Testing considerations

- Manual: edge hits on paddle corners; rapid paddle movement under ball.
- Unit: rectangle vs circle overlapping predicate with known positions.
- Regression: after brick added, verify ball does not “tunnel” through thin rows.

---

## Documentation and evidence

- Diagram: paddle hit regions (current flat bounce vs. future segmented paddle).
- Clip: brick chain reaction clears.

---

## Open questions and decisions

- Whether paddle bounce uses ball entry direction or only position.
- Single brick per frame vs. resolving multiple contacts (rare at low speed).
