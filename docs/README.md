# Project Documentation Index

Centralized entry point for in-repo documentation. Additional design docs and specifications should be added here rather than cluttering the repository root.

## Index

- [Extensibility & Customization](./EXTENSIBILITY.md)
- [Widgets & Node/Block Types](./Nodes.md)
- [Project Notes](./Notes.md)
- [Contributing Manifests](./ContributingManifests.md)
- (Planned) Packs & Distribution Guide
- (Planned) Schema Evolution & Compatibility Policy
- (Planned) Runtime Compilation / Hot Reload Architecture
- (Planned) Theming & UI Style Guidelines

## Conventions

- Prefer small, focused documents grouped by topic.
- Cross-link instead of duplicating content.
- Keep example code minimal; link to source instead of embedding large snippets.

## Adding New Docs

1. Create a new markdown file under `docs/` with a concise name (PascalCase or hyphenated).
2. Add an entry to the Index above.
3. If the document supersedes root-level content, replace the old file with a stub pointer.
4. Update `.dev/markers/commit_message.txt` if part of a larger feature or refactor.

## Roadmap for Docs (High-Level)

| Topic | Status | Notes |
|-------|--------|-------|
| Extensibility | Initial | Groundwork + customization pack concept documented |
| Packs Guide | Planned | Describe installation, caching, verification |
| Schema Evolution | Planned | Backward-compat policy & deprecation workflow |
| Runtime Compilation | Planned | RCC++ integration, safety, versioning |
| Theming | Planned | Style tokens, palette overrides |

---
This index will expand as the project matures.
