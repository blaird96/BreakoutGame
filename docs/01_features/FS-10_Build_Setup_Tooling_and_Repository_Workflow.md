# FS-10: Build Setup, Tooling, and Repository Workflow

**Category:** Engineering Support  
**Priority:** High  

---

## Status (as of 2026-04-01)

| Field | Value |
| --- | --- |
| **Implementation status** | Partial |
| **Primary evidence** | [`README.md`](../../README.md), [`.vscode/tasks.json`](../../.vscode/tasks.json), single translation unit [`main.cpp`](../../main.cpp) |
| **Gaps** | Machine-specific absolute paths on `C:\`; no CMake/presets; no documented Git branching rules; `docs/02_management/` management docs (e.g. Task Board) not in current repository tree; team workflow not fully captured in repo |

---

## Purpose and scope

**Owns:** Toolchain selection, dependency versions, build/run instructions, recommended IDE integration, repository layout expectations, and team workflow conventions (branching, reviews) as **documented process**.

**Out of scope:** Gameplay rules (FS-01–FS-09); test case design detail (FS-11) except build of tests.

---

## Definitions

- **SFML 3.0.2:** Graphics library version referenced in `README.md`.
- **MinGW 32-bit (i686):** Compiler distribution per README (“32-Bit GCC 14.2.0 MinGW (DW2) (UCRT)”).

---

## Data model and attributes (repository facts)

| Artifact | Attribute | Current value |
| --- | --- | --- |
| Compiler path (tasks.json) | `command` | `C:\mingw32\bin\g++.exe` |
| SFML include | `-I` | `C:\SFML-3.0.2\include` |
| SFML lib | `-L` | `C:\SFML-3.0.2\lib` |
| Linked libs | `-l` | `sfml-graphics`, `sfml-window`, `sfml-system` |
| Build mode | tasks | “build active file”; `${file}` compiles selected file |
| Output | `-o` | `${fileDirname}\${fileBasenameNoExtension}.exe` |

---

## Functional requirements

1. **FS-10.1** The project SHALL document compiler version expectations and SFML version for reproducible builds.
2. **FS-10.2** The project SHALL document environment setup (PATH, extracted folder locations) for the primary target OS.
3. **FS-10.3** The repository SHOULD provide a one-command or IDE-documented build path for `main.cpp` (or future targets).
4. **FS-10.4** The team SHOULD document branch naming, review expectations, and integration rhythm (populate Decision Log / Task Board).
5. **FS-10.5** (Target) Replace or supplement absolute paths with CMake, `compile_flags.txt`, or env-var-based tasks for portability.

---

## Non-functional requirements

- **NFR-01** A new team member following README SHOULD reach a running executable on a standard lab/home PC matching assumptions **or** hit a clearly documented blocker.
- **NFR-02** Repository SHOULD avoid committing large binary SDKs; use local installs as README describes.

---

## Dependencies

- **Enables:** All FS features (executable delivery).

---

## Interfaces and events

**Developer-facing**

- README prose instructions.
- VS Code `tasks.json` cppbuild task.
- (Future) CI workflow file if added.

---

## Acceptance criteria

- [ ] README matches actual SFML version and folder names used in `tasks.json`.
- [ ] Fresh clone + documented setup produces `main.exe` (or equivalent) on team baseline machine.
- [ ] Known DLL placement for SFML runtime is documented (Windows) if dynamic linking.
- [ ] Task Board records current tasks (non-empty) before mid/late milestones.

---

## Implementation notes

**As-built:** Hard-coded `C:\` paths in `.vscode/tasks.json`; README prescribes extracting `mingw32` and `SFML-3.0.2` to `C:\`.

**Target:** CMake with `FetchContent` or find_package, or document `SFML_DIR` env substitution in tasks.

---

## Testing considerations

- Manual: second machine clone test by teammate.
- Optional: scripted `g++` one-liner in README matching tasks args.

---

## Documentation and evidence

- Screenshot: successful terminal `g++ --version` from README.
- Final Report: toolchain subsection.

---

## Open questions and decisions

- Standardize on 32 vs 64-bit across all members (README argues 32-bit ubiquity).
- Whether to vendor a `launch.json` for debugging.
