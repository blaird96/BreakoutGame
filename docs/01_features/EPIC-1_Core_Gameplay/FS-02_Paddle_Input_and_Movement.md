# FS-02: Paddle Input and Movement

**Category:** Core Gameplay  
**Priority:** High  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Partial |
| **Primary evidence** | [`main.cpp`](../../main.cpp) lines 5–7, 34–43, 43 |
| **Gaps** | Movement is **per-frame** (0.1 px) not time-based; no key repeat policy beyond `isKeyPressed`; no alternate input (gamepad) |

### 2026-04-09 Addendum

- **Updated implementation status:** Mostly complete (~75%)
- **Current evidence:** `Game.cpp` (`handleInput`), `GameConstants.h`, `GameHelpers.h`
- **Complete now:** Arrow + WASD support, clamped horizontal bounds, dt-based paddle movement (`PaddleSpeedPxPerSec * dt`), centralized clamp helper usage.
- **Partially complete:** Simultaneous opposite-key behavior still implicit (`if`/`else if`), no alternate input device support.
- **Outstanding:** Formalize key-conflict behavior, add test evidence for edge-input behavior, and document final control policy.

---

## Purpose and scope

**Owns:** Mapping player keyboard input to horizontal paddle motion and clamping to playable bounds.

**Out of scope:** Ball physics (FS-03), collision normals (FS-05), scoring (FS-06), on-screen controls UI (FS-08).

---

## Definitions

- **Paddle center:** `RectangleShape` position after origin offset; prototype origin `(75, 10)` for size 150×20 → center-aligned paddle.
- **Playable horizontal span (prototype):** center x clamped implicitly by edge positions 85 ≤ x ≤ 715 at y = 790.

---

## Data model and attributes

| Attribute | Type / value | Notes |
| --- | --- | --- |
| `paddle_size` | (150, 20) px | `RectangleShape` constructor |
| `paddle_origin` | (75, 10) px | center pivot |
| `paddle_initial_position` | (400, 790) | `setPosition` |
| `paddle_y` | 790 | fixed row |
| `move_delta` | 0.1f | per frame if key held |
| `x_min` | 85.f | left clamp |
| `x_max` | 715.f | right clamp |
| **Keys (left)** | `Left`, `A` | `sf::Keyboard` |
| **Keys (right)** | `Right`, `D` | `sf::Keyboard` |

Coordinates: pixel space, SFML default (y down).

---

## Functional requirements

1. **FS-02.1** The system SHALL move the paddle left when the left-move key is pressed and right when the right-move key is pressed.
2. **FS-02.2** The system SHALL keep the paddle within defined horizontal bounds so it does not leave the playfield.
3. **FS-02.3** The system SHALL use keyboard polling appropriate to the main loop (current: `isKeyPressed` each frame).
4. **FS-02.4** (Target) Movement SHOULD scale with elapsed time so speed is consistent across frame rates.

---

## Non-functional requirements

- **NFR-01** Input latency SHOULD remain imperceptible at typical frame rates on target hardware (prototype: same-thread poll).

---

## Dependencies

- **Requires:** FS-01 (window/input context).
- **Relates to:** FS-05 (paddle geometry used for ball bounce).

---

## Interfaces and events

**Inputs:** `sf::Keyboard::Key::Left`, `A`, `Right`, `D`.

**Outputs:** Updated `paddle.setPosition` each frame when keys held.

---

## Acceptance criteria

- [ ] Holding Left/A moves paddle left until it stops at the left bound.
- [ ] Holding Right/D moves paddle right until it stops at the right bound.
- [ ] Paddle does not leave visible play area under sustained input.
- [ ] (Target) Documented px/sec or units/sec if delta-time refactor lands.

---

## Implementation notes

**As-built:** Conditional branches with ternary clamp (`main.cpp` 35–39). Speed 0.1f per frame.

**Target:** `paddleVelocity * deltaTime`; centralize bounds from playfield constants shared with FS-03 wall positions.

---

## Testing considerations

- Manual: hold each direction for 10+ seconds at windowed mode; verify clamp.
- Manual: tap keys — paddle moves incrementally per frame.
- Future unit test: pure function `clampPaddleX(desiredX, min, max)`.

---

## Documentation and evidence

- User guide: key bindings (partially in README; align with FS-12).
- Screenshot: paddle at left and right extremes.

---

## Open questions and decisions

- Final bounds vs. brick grid width once FS-04 defines margins.
- Whether diagonal or simultaneous left+right resolves to no movement (currently `else if` — right wins if both pressed).
