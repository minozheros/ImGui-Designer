# Project Notes (Relocated)

> Migrated from root `NOTES.md` to `docs/Notes.md` to keep the repository root uncluttered.

(Original content below, unchanged except for path-sensitive references.)

---

## Original Title

## 📋 IMPORTANT: Read First

**Before reading this file, please read `.github/instructions/first.instructions.md`** - it contains essential project rules, workflow guidelines, and coding standards that must be followed.

**Note:** If there is any conflicting information between this file and `first.instructions.md`, `first.instructions.md` takes precedence.

## Workflow Rule: Periodic Rereading of Project Rules (added 23. September 2025)

To ensure strict compliance and avoid context drift, the assistant must reread all project rules and instructions (from `.github/instructions/first.instructions.md`, `docs/Notes.md`, and any other policy files) after every 3 code or file changes, or before starting any new major feature or refactor. This rereading will be handled automatically as part of the workflow, without extra comments or notifications, so the process remains seamless and unobtrusive. This guarantees that all actions remain aligned with the latest requirements and conventions.

**Rationale:**

- Prevents forgetting or drifting from project rules during long or complex sessions
- Ensures all code and workflow changes remain compliant
- Aids onboarding and consistency for all contributors

## Project Structure Overview (as of 23. September 2025)

(Section truncated for brevity — refer to repository structure for current layout.)

---

For full historical details, refer to git history of the original `NOTES.md` if needed.

---

## Marker & Transient Files Convention (added 26. September 2025)

To keep the repository root clean, all transient marker / sentinel files and helper commit message scratch file live under `.dev/markers/`.

### Directory

`/.dev/markers/` (ignored by default via `.gitignore`).

### Current Files

- `commit_message.txt` – staging area for the next commit message (overwrite before committing).
- `node_factory_map_generated.ok` – touched when `NodeFactoryMap.hpp` generation succeeds.
- `param_structs_generated.ok` – (reserved) will be touched after ImGui param structs generation.
- `node_params_map_generated.ok` – (reserved) will be touched after node params map generation.

### Purpose of *.ok Markers

These zero‑byte (or near zero) files provide stable, timestamp-sensitive dependencies for CMake custom commands. They let us:

1. Express completion of multi-step Python script generation.
2. Avoid regenerating downstream targets when inputs have not changed.
3. Group multiple generated artifacts behind a single dependency edge.

### Naming Pattern

`<feature>_<artifact>_generated.ok`

Keep names deterministic and avoid adding semantic meaning beyond build dependency signaling.

### Adding a New Marker

1. Add generation logic to the relevant CMake file using `MARKER_DIR` (see `cmake/generators/GenerateImGuiApiInfo.cmake`).
2. Touch the marker after the script succeeds: `COMMAND ${CMAKE_COMMAND} -E touch ${MARKER_DIR}/your_marker.ok`.
3. Add it to a custom target if other targets must depend on it.
4. (Optional) Add to `GENERATED_FILES` list if it should be cleaned by `clean_generated`.

### Do Not Commit Markers (Usually)

Markers are ignored in Git; only commit them deliberately when debugging build graph behavior.

### Rationale

- Reduces root noise.
- Centralizes ephemeral build state.
- Keeps future automation predictable.

---
