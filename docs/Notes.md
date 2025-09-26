# Project Notes (Relocated)

> Migrated from root `NOTES.md` to `docs/Notes.md` to keep the repository root uncluttered.

(Original content below, unchanged except for path-sensitive references.)

---

## Original Title

## 📋 IMPORTANT: Canonical Rules

All binding project rules now live exclusively in `.github/instructions/first.instructions.md`.
This file only carries contextual notes, rationale breadcrumbs, or historical commentary. If you think a rule is missing, add it to `first.instructions.md`—not here.

## Meta: Reread Policy (Historical Note)

Periodic reread logic (every 3 edits / before major feature) is implemented implicitly. Rationale retained here for posterity:

- Prevent context drift
- Maintain rule compliance over long sessions
- Aid onboarding consistency

## Project Structure Overview (as of 23. September 2025)

(Section truncated for brevity — refer to repository structure for current layout.)

---

For full historical details, refer to git history of the original `NOTES.md` if needed.

---

## Marker & Transient Files Convention (summary)

To keep the repository root clean, all transient marker / sentinel files and helper commit message scratch file live under `.dev/markers/`.

### Directory

`/.dev/markers/` (ignored via `.gitignore`).

### Current Files

- `commit_message.txt`
- `node_factory_map_generated.ok`
- `param_structs_generated.ok` (reserved)
- `node_params_map_generated.ok` (reserved)

### Purpose

Sentinel dependencies for CMake custom commands (completion, change tracking, grouping).

### Naming Pattern

`<feature>_<artifact>_generated.ok`

Keep names deterministic and avoid adding semantic meaning beyond build dependency signaling.

### Adding a New Marker (See first.instructions.md for full procedure)

1. Add generator logic referencing `MARKER_DIR`.
2. Touch after success.
3. Add dependency edges.
4. Add to clean list if appropriate.

### VCS Policy

Ignored by default; commit only for build graph analysis.

### Rationale

Reduce root noise • centralize ephemeral state • keep automation predictable.

---
