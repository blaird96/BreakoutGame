# FS-09: Audio and Optional Enhancement Support

**Category:** Stretch / Enhancement  
**Priority:** Low to Medium  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Not started |
| **Primary evidence** | [`main.cpp`](../../main.cpp) includes only `SFML/Graphics.hpp`; [`.vscode/tasks.json`](../../.vscode/tasks.json) links graphics, window, system — not audio |
| **Gaps** | No `sfml-audio`, no buffers/music, no volume control; other stretch items (levels, pause) tracked here as optional |

### 2026-04-09 Addendum

- **Updated implementation status:** Early/partial (~20%)
- **Current evidence:** No `sfml-audio` linkage or runtime audio subsystem in current code path.
- **Complete now:** Some optional-adjacent UX pieces (menu/settings flow) exist, but FS-09 audio functionality itself remains unimplemented.
- **No longer relevant/obsolete:** Legacy references that treat `src/main.cpp` as the only runtime path are outdated.
- **Outstanding:** Add audio library linkage, event-based SFX/music hooks, asset and license handling, and decide whether multi-level progression belongs to this term scope.

---

## Purpose and scope

**Owns:** Optional product polish: sound effects, music, pause, multiple levels, and non-critical visual effects beyond core HUD.

**Out of scope:** Tier-1 correctness (must work silent); mandatory requirements in FS-01–FS-08.

---

## Definitions

- **SFX:** Short buffered sounds (brick break, paddle hit, lose life).
- **BGM:** Looping music during menu or gameplay.

---

## Data model and attributes (target)

| Attribute | Description |
| --- | --- |
| `SoundBuffer` assets | Files under e.g. `assets/audio/` |
| `Sound`, `Music` instances | SFML audio types |
| `masterVolume` | 0.0–1.0 optional |
| `LevelConfig` | If multi-level — references brick layout, ball speed |

---

## Functional requirements

1. **FS-09.1** (If in scope) The system MAY play a sound when the ball hits the paddle or a brick.
2. **FS-09.2** (If in scope) The system MAY play a sound or music track on life lost or game state changes.
3. **FS-09.3** (If in scope) The system MAY implement pause that halts simulation and audio ducking.
4. **FS-09.4** (If in scope) The system MAY load additional levels after clearing bricks.
5. **FS-09.5** Build instructions SHALL be updated if `sfml-audio` and DLL dependencies are added (FS-10).

---

## Non-functional requirements

- **NFR-01** Missing audio files MUST NOT crash release build (graceful skip or log).
- **NFR-02** Asset sizes SHOULD remain reasonable for Git and course submission.

---

## Dependencies

- **Requires:** FS-10 toolchain adding audio libraries; optional asset pipeline (FS-12 checklist).
- **Hooks:** FS-05/FS-06 events for triggers.

---

## Interfaces and events

**Suggested API**

- `void playSfx(SfxId id);`
- `void playMusic(MusicId id, bool loop);`
- `void setMuted(bool);`

---

## Acceptance criteria

- [ ] If audio enabled, triggering events produces audible feedback without pops or leaks on exit.
- [ ] If audio disabled or files missing, game still runs.
- [ ] README documents extra DLLs for OpenAL / SFML audio on Windows if required by SFML distribution.

---

## Implementation notes

**As-built:** Silent game.

**Target:** Add `-lsfml-audio` and verify MinGW SFML distribution includes matching audio DLLs; load buffers at startup.

---

## Testing considerations

- Manual: rapid brick breaks — no channel exhaustion or crash.
- Manual: volume off / Windows mixer interaction.

---

## Documentation and evidence

- List of assets and licenses in Final Report.
- Optional clip with sound for demo.

---

## Open questions and decisions

- Which stretch items are formally in scope for Spring 2026.
- Royalty-free asset sources vs. generated beeps.
