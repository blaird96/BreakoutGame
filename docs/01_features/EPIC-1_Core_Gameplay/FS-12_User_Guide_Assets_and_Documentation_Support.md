# FS-12: User Guide Assets and Documentation Support

**Category:** Documentation Support  
**Priority:** Medium  

> **Overlap review note:** Setup/troubleshooting content that is developer-facing overlaps with `docs/development.md`. Review duplicate build/dependency guidance in this spec before final documentation cleanup (do not delete yet).

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Partial |
| **Primary evidence** | [`README.md`](../../README.md) — SFML/MinGW setup, VS Code intent, controls partially implied via FS-02 spec (not all copied to README yet) |
| **Gaps** | No dedicated User Guide markdown/PDF; screenshot checklist not completed; troubleshooting limited; Final Report asset list not populated |

### 2026-04-09 Addendum

- **Updated implementation status:** Partially complete (~50%)
- **Current evidence:** `README.md` expanded setup/controls/limitations, `docs/02_management/Phase1_Test_Checklist.md`
- **Complete now:** Stronger build/run and controls guidance; documented manual test evidence artifact.
- **Partially complete:** Dedicated user-guide deliverable package and evidence mapping to all FS IDs are still incomplete.
- **Outstanding:** Create final User Guide document, capture labeled screenshots/media, and add finalized attribution/troubleshooting sections for submission readiness.

---

## Purpose and scope

**Owns:** End-user facing instructions, asset inventory (fonts, audio if any), screenshot/video checklist, and materials that prove requirements in the Final Report.

**Out of scope:** Feature implementation (other FS); internal QA procedure detail (FS-11) though evidence overlaps.

---

## Definitions

- **User Guide:** Standalone document a grader or player uses without reading source.
- **Evidence bundle:** Screenshots + short description mapping to blueprint/requirements.

---

## Data model and attributes (checklist)

Capture as files accrue (paths team-defined, e.g. `docs/03_deliverables/assets/`):

| Asset | Purpose | Status (fill in as completed) |
| --- | --- | --- |
| Screenshot: window + title | FS-01 | [ ] |
| Screenshot: paddle at extents | FS-02 | [ ] |
| Screenshot: ball bouncing | FS-03 | [ ] |
| Screenshot: brick grid | FS-04 | [ ] |
| Screenshot: collision mid-game | FS-05 | [ ] |
| Screenshot: HUD score/lives | FS-06/FS-08 | [ ] |
| Screenshot: win / game over | FS-06/FS-07 | [ ] |
| Short clip or GIF (optional) | Demo | [ ] |
| Copy of controls table | FS-02, FS-07 | [ ] |
| Font license file | FS-08 | N/A until font added |
| Audio credits | FS-09 | N/A until audio added |

---

## Functional requirements

1. **FS-12.1** The project SHALL supply setup instructions sufficient to build and run the game on the documented platform (see README — keep synchronized with FS-10).
2. **FS-12.2** The User Guide SHALL list player controls and how to start/restart/pause (once FS-07 defines keys).
3. **FS-12.3** The team SHALL capture dated screenshots or video for major features before final submission.
4. **FS-12.4** The documentation SHALL note known limitations (e.g. path-specific build, resolutions supported).
5. **FS-12.5** Third-party assets SHALL include license/attribution in the guide or appendix.

---

## Non-functional requirements

- **NFR-01** Instructions SHOULD be stepwise and testable by someone outside the team.
- **NFR-02** File names SHOULD be stable (no spaces) for LMS uploads.

---

## Dependencies

- **Requires:** Implemented features for meaningful screenshots; FS-08 for readable on-screen text.

---

## Interfaces and events

**Deliverable shapes**

- Markdown User Guide in `docs/03_deliverables/` (or PDF export).
- PowerPoint/Google Slides only if course requires — still mirror content from this checklist.

---

## Acceptance criteria

- [ ] Reader can install dependencies and run the game using only project docs.
- [ ] Controls and objective of the game (“clear bricks”) explained in plain language.
- [ ] Evidence folder contains labeled images mapping to FS / blueprint clauses.
- [ ] Troubleshooting section lists common SFML DLL/path errors on Windows.

---

## Implementation notes

**As-built:** README covers toolchain; expand with `CONTROLS.md` or section in User Guide draft as FS-07 stabilizes.

**Target:** Single table: Requirement (Blueprint §) → Evidence file name.

---

## Testing considerations

- Peer review: someone not on the team follows README cold.
- Verify all links in markdown resolve for graders using relative paths.

---

## Documentation and evidence

- Align captions with Feature Spec IDs for traceability (e.g. “FS-04 Brick grid at level start”).
- Store high-resolution originals plus compressed copies if needed.

---

## Open questions and decisions

- Final document template from instructor (UMGC-specific).
- Whether to embed screenshots in README vs. separate guide only.
