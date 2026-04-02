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
| Automated tests | Future: `tests/` + CMake + GoogleTest or Catch2 — **not present** |
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

**Target:** Extract `Collision` namespace with no SFML deps for unit tests; keep rendering in integration manual tests.

---

## Testing considerations (starter matrix)

- Manual: 5-minute idle run — memory/CPU sanity.
- Manual: lose all lives post FS-06 fix — verifies game over.
- Manual: clear bricks — verifies win.
- Unit (future): circle vs AABB hit test vectors.

---

## Documentation and evidence

- Export or PDF of test results for capstone packet.
- Bug fix commits referenced in Evidence Log.

---

## Open questions and decisions

- Choice of unit test framework and whether to mandate it for all members’ environments.
- Formal severity rubric (blocker / major / minor).
