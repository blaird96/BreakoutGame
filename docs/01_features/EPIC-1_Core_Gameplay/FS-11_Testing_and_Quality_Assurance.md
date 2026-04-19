# FS-11: Testing and Quality Assurance

**Category:** Quality Assurance  
**Priority:** High  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Not started (no automated harness in repository) |
| **Primary evidence** | This specification; manual play of [`main.cpp`](../../main.cpp) build expected but not scripted |
| **Gaps** | No unit test framework, no CI, no recorded test matrix in docs; evidence log not verified in this pass |

### 2026-04-09 Addendum

- **Updated implementation status:** Partially complete (~60%)
- **Current evidence:** `tests/` harness and unit tests, `docs/02_management/Phase1_Test_Checklist.md`
- **Complete now:** Basic automated helper/state tests and a dated manual execution checklist with pass/fail results.
- **Partially complete:** No CI pipeline yet; test-to-feature traceability and defect workflow are still lightweight.
- **Outstanding:** Add CI build/test automation, formalize defect tracking severity and process, and expand regression coverage for gameplay integration paths.

### 2026-04-19 Addendum

- **Updated implementation status:** Partially complete (~70%)
- **Current evidence:** Same as above, plus [`tests/Collision2DTests.cpp`](../../../tests/Collision2DTests.cpp) for pure circle–AABB collision math; root `CMakeLists.txt` wires `breakout_tests` when `BUILD_TESTING=ON` (matches [`CMakePresets.json`](../../../CMakePresets.json) `tests-debug`).
- **Complete now:** Deterministic unit coverage for helpers, game manager state, physics reflections, and **collision resolution predicates** without running the SFML game loop.
- **Outstanding:** CI on push/PR; broader integration tests (full `Game` loop) remain manual or future work.

---

## Purpose and scope

**Owns:** What to test, how (manual vs automated), when (per milestone), expected outcomes, defect logging, and regression discipline for the Breakout project.

**Out of scope:** Writing course prose for Final Report (but feeds evidence); implementing production metrics.

---

## Definitions

- **Smoke test:** Launch executable, verify window opens and closes cleanly.
- **Regression test:** Previously passing behavior rechecked after a change.

---

## Data model and attributes

| Artifact | Location / format |
| --- | --- |
| Test matrix | Spreadsheet or markdown table (team choice) — recommend `docs/02_management/` or appendix |
| Defect log | Issue tracker or `Evidence_Log.md` / team template |
| Automated tests | `tests/` lightweight harness (`TestHarness.h`) + `CTest` via root [`CMakeLists.txt`](../../../CMakeLists.txt); optional [`scripts/build-tests.ps1`](../../../scripts/build-tests.ps1) |
| CI job | Future: GitHub Actions or similar |

---

## Functional requirements

1. **FS-11.1** The team SHALL maintain a documented list of test cases covering each Tier-1 Feature Specification (FS-01–FS-06, FS-10).
2. **FS-11.2** The team SHALL execute smoke tests before each demonstration or submission milestone.
3. **FS-11.3** The team SHALL record defects with reproduction steps and severity.
4. **FS-11.4** (Target) Core logic (collision, grid queries) SHOULD have automated unit tests where pure extraction is possible.
5. **FS-11.5** (Target) CI SHOULD build the project on push or PR if toolchain becomes portable.

---

## Non-functional requirements

- **NFR-01** Testing approach SHOULD be proportionate: prioritize manual gameplay for SFML integration risks; add units for deterministic math.
- **NFR-02** Evidence SHOULD be archivable (screenshots, short logs) for course grading.

---

## Dependencies

- **Requires:** Executable from FS-10; feature-complete enough to have meaningful cases for FS-04 and FS-06.

---

## Interfaces and events

**Per-feature smoke anchors**

- FS-01: launch/close
- FS-02: bounds
- FS-03: wall bounce, miss reset
- FS-04: grid visible
- FS-05: brick + paddle hits
- FS-06: score/lives/win/loss
- FS-07/08: flows readable
- FS-09: audio toggle if implemented

---

## Acceptance criteria

- [ ] Written test checklist exists and maps to FS IDs (traceability).
- [ ] At least one recorded test run per sprint or milestone (date + tester + result).
- [ ] Known critical defects listed as blockers before declaring milestone done.
- [ ] (Stretch) Automated test binary runs in CI green.

---

## Implementation notes

**As-built:** Strategy-only; implement checklist in `Evidence_Log` or dedicated QA doc per team preference.

**As-built (2026-04-19):** `Collision2D` in [`src/Collision2D.h`](../../../src/Collision2D.h) is SFML-free; Phase I `Game` links it for runtime collision. Rendering and full gameplay remain integration-tested manually.

---

## Testing considerations (starter matrix)

- Manual: 5-minute idle run — memory/CPU sanity.
- Manual: lose all lives post FS-06 fix — verifies game over.
- Manual: clear bricks — verifies win.
- Unit: circle vs AABB overlap and resolution (`Collision2DTests.cpp`).

---

## Documentation and evidence

- Export or PDF of test results for capstone packet.
- Bug fix commits referenced in Evidence Log.

---

## Open questions and decisions

- Choice of unit test framework and whether to mandate it for all members’ environments.
- Formal severity rubric (blocker / major / minor).
