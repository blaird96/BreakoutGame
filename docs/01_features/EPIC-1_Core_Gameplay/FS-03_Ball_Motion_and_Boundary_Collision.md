# FS-03: Ball Motion and Boundary Collision

**Category:** Core Gameplay  
**Priority:** High  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Partial |
| **Primary evidence** | [`main.cpp`](../../main.cpp) lines 9–13, 45–58 |
| **Gaps** | No ball “waiting on paddle” launch state; wall collision uses position thresholds not generalized normals; bottom loss couples to lives in same block (see FS-06) |

### 2026-04-09 Addendum

- **Updated implementation status:** Partially complete (~70%)
- **Current evidence:** `Game.cpp` (`applyBallLaunchVelocity`, `update`, `resetBall`), `GameConstants.h`
- **Complete now:** dt-scaled motion, configurable speed constants, wall/ceiling reflection, randomized serve direction/speed, pause-on-reset launch flow.
- **Partially complete:** Collision response remains threshold-based and tightly coupled to gameplay update flow.
- **Outstanding:** Improve directional collision resolution robustness, reduce magic-threshold behavior, and further decouple miss/life transitions from physics update logic.

---

## Purpose and scope

**Owns:** Ball position integration, velocity vector, reflection off top and side “walls,” baseline reset after ball leaves bottom of play area, and interaction hooks for paddle (FS-05) at a vertical band.

**Out of scope:** Brick destruction (FS-04/FS-05), scoring (FS-06), HUD (FS-08).

---

## Definitions

- **Velocity `velocity`:** `sf::Vector2f` added to position each frame (prototype: (0.1f, -0.1f) initially).
- **Miss:** Ball center `y > 805.f` triggers reset path in prototype (`main.cpp` 54–58).

---

## Data model and attributes

| Attribute | Value | Notes |
| --- | --- | --- |
| `ball_radius` | 14.f | `CircleShape` |
| `ball_origin` | (radius, radius) | center origin |
| `ball_initial_position` | (400, 766) | after setup |
| `velocity_initial` | (0.1f, -0.1f) | up-right in SFML coords |
| Wall bounce x thresholds | x ≥ 776 or x ≤ 24 | invert `velocity.x` |
| Ceiling bounce | y ≤ 24 | invert `velocity.y` |
| Paddle bounce band | y ≥ 780 + horizontal overlap | invert `velocity.y` (see FS-05) |
| Miss threshold | y > 805 | decrement life, reset ball (FS-06) |

Playfield visual walls sit near 10 and 790; numeric thresholds differ slightly from line coordinates (tuning debt).

---

## Functional requirements

1. **FS-03.1** The system SHALL update ball position every frame by adding the velocity vector.
2. **FS-03.2** The system SHALL reflect the ball horizontally when it intersects or passes left/right bounds (invert x component of velocity).
3. **FS-03.3** The system SHALL reflect the ball off the top bound (invert y component).
4. **FS-03.4** The system SHALL define a behavior when the ball passes below the play area (prototype: reset position and velocity; interacts with FS-06 lives).
5. **FS-03.5** (Target) Wall reflection SHOULD use consistent geometric rules (normals, penetration resolution) shared with FS-05.

---

## Non-functional requirements

- **NFR-01** Ball motion SHOULD remain stable (no unbounded speed growth) under normal play.
- **NFR-02** (Target) Speed SHOULD be configurable or derived from level/design constants.

---

## Dependencies

- **Requires:** FS-01 loop.
- **Interacts with:** FS-05 (paddle bounce), FS-06 (lives on miss).

---

## Interfaces and events

**Inputs:** Current paddle position (read for paddle bounce in same translation unit).

**Outputs:** Updated `ball` position and `velocity`; side effect on `lives` in prototype when miss (`main.cpp` 54–56).

---

## Acceptance criteria

- [ ] Ball moves continuously while the window is open.
- [ ] Ball reflects off left, top, and right boundaries without leaving the window indefinitely in a corner case test of several minutes.
- [ ] Ball resets after falling below threshold (visual check).
- [ ] (Target) Miss and bounce rules documented with a diagram in User Guide.

---

## Implementation notes

**As-built:** Axis-aligned flip on threshold comparisons; paddle test only checks y band and x relative to paddle center ± 75 (`main.cpp` 46–52).

**Target:** Extract `updateBall(dt)`, `resolveWallCollisions`, share constants with border drawing.

---

## Testing considerations

- Manual: observe wall bounce symmetry over multiple hits.
- Manual: verify miss resets ball to starting position and velocity.
- Future: unit tests for reflect helper with known vectors.

---

## Documentation and evidence

- Short clip: ball in motion and bouncing.
- Note in Final Report: frame-rate dependence of speed.

---

## Open questions and decisions

- Align numeric bounce thresholds with drawn line at x=10/790 and y=10 accounting for ball radius.
- Whether bottom “death line” should be exactly at paddle row or below it (currently 805).
