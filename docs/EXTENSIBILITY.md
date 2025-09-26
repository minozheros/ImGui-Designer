# Extensibility (Groundwork)

This document outlines reserved scaffolding for future runtime‑replaceable components in ImGui-Designer. None of the interfaces described here are currently wired into the application logic; they exist so that upcoming schema, pack, and runtime work has stable identifiers to target.

## Goals

- Allow packs / users / runtime-compiled modules to provide alternative renderers, adapters, layout engines, and frame hooks.
- Keep the *declarative* layer (JSON descriptors + schema) ahead of the *imperative* runtime so we can evolve without breaking existing manifests.
- Support layered override precedence in the future (Session > User > Pack > Descriptor > Core).

## Schema Touchpoint: `uiAdapters`

Defined in `schemas/LibraryDescriptor.schema.json`:

Adapter fields (summary):

- `id`: unique within descriptor
- `kind`: one of: type, function, enum, macro, constant, panel, frameStage, layout
- `adapterType`: valueRenderer | blockRenderer | panelRenderer | frameHook | layoutEngine | custom
- `target`: qualified symbol or conceptual id (optional for some future roles)
- `stages`: array of frame lifecycle stage names (for frame hooks)
- `provides` / `dependsOn`: capability graph & ordering hints
- `status`: EXPERIMENTAL | STABLE | INTERNAL
- `tags`, `since`, `doc`: metadata

Nothing consumes these yet—they are placeholders.

## Frame Hook Stages (Proposed Set)

Enumerated in `IFrameHook`:

1. `BeginFrame`
2. `PreUpdate`
3. `GraphResolve`
4. `Panels`
5. `Overlays`
6. `LateDecorators`
7. `RenderSubmit`
8. `PostFrame`

Stages may expand; adapters should tolerate unknown future stages (defensive design once implemented).

## Interfaces Overview (All header-only declarations)

Location: `src/app/ext/`

| Interface | Purpose |
|-----------|---------|
| `IReplaceable` | Marker base class |
| `ITypeAdapter` | Value/type-level adaptation (editing, serialization, preview) |
| `IBlockRenderer` | Custom block visual/interaction implementation |
| `IPanelRenderer` | Custom tool or data panel renderer |
| `IFrameHook` | Per-frame lifecycle injections (one instance can handle multiple stages) |
| `ILayoutEngine` | Graph/block layout strategy implementation |
| `ReplaceableRegistry<T>` | Simple id→shared_ptr registry (single-layer for now) |
| `registrySingleton<T>()` | Access global registry instance |

All interfaces are intentionally minimal—no allocation or ownership policies yet.

## Future Roadmap (Non-binding)

1. Runtime discovery via RCC++ or plugin manifests.
2. Layered registry views (compose multiple sources with precedence rules).
3. Hot reload safety (quiescent state detection before replacement).
4. Metrics & tracing hooks around adapters.
5. Dependency graph resolution (topological order on `dependsOn`).
6. Validation tying `uiAdapters` entries to provided runtime implementations.

## Design Notes

- Simplicity first: Avoid overcommitting to ABI/plugin stability before requirements gel.
- Header-only patterns ease early experimentation; promotion to compiled units can come later.
- `layoutEngine` reserved early to avoid schema churn once layout customization lands.
- `frameHook` uses an enum now; a string-driven extension layer could wrap it later if necessary.

## Contributing Extensions (Future)

For now: do not implement concrete subclasses inside core unless you are preparing a prototype. When runtime wiring begins, we will introduce:

- Registration macros.
- Validation pass ensuring declared adapters have implementations (and vice versa).
- Optional capability negotiation (packs can declare required capabilities).

---
This file will evolve as the extensibility system matures.

## Customization Pack Concept (Planned)

To keep the core lean while enabling deep user-driven UI and behavior overrides, we plan a separate optional "Customization Pack" that supplies adapters, alternative visuals, and tooling.

### Objectives

- Ship curated alternative layout engines, block render styles, panels, and frame hooks.
- Provide a user-facing panel to activate/deactivate or switch among registered adapters.
- Allow exporting the currently active override set as a *user overlay pack* (reproducible + shareable).
- Enable progressive enhancement: core works without the pack; adding the pack unlocks advanced customization.

### Layering & Precedence (Target Model)

`Core < Descriptor < Pack < UserPack < Session`

Where:

- **Core**: Built-in defaults.
- **Descriptor**: Library-provided adapters declared in its descriptor.
- **Pack**: The customization pack's shipped adapters.
- **UserPack**: Generated from user actions (exported overlay pack on disk).
- **Session**: Ephemeral runtime choices not yet persisted.

### Planned Phases

1. **Phase 1 – Passive Declarations**: Pack adds `uiAdapters` entries only (no runtime activation).
2. **Phase 2 – Discovery (Log-Only)**: Core scans active packs; logs resolvable adapters and potential conflicts.
3. **Phase 3 – Activation (Selective)**: Layout engine + one frame hook type activated via registries.
4. **Phase 4 – UI Control**: Customization panel for selecting active layout engine, block renderer, frame hooks.
5. **Phase 5 – Export Overlay**: Persist active selections as a generated user pack (JSON + stub code if needed).
6. **Phase 6 – Live Editing**: Inline RCC++ editor modifies adapter implementations and hot-swaps them safely.
7. **Phase 7 – Capability Negotiation**: Packs declare required capabilities; resolver reports unmet requirements.

### Adapter Categories the Pack Might Provide

- **layoutEngine**: `dagLayered`, `forceDirected`, `orthogonalRoute` variants.
- **blockRenderer**: `compact`, `verbose`, `darkglass` themes.
- **frameHook**: FPS/memory overlay, graph validator, hot-reload notifier, telemetry collector.
- **panelRenderer**: Customization UI, Metrics dashboard, Override diff viewer.
- **type/value adapters**: Rich editors for vectors, colors, ranges, and flagged enums.

### Example User Config (Future)

```json
{
  "active": {
    "layoutEngine": "dagLayered",
    "blockRenderer": "compact",
    "frameHooks": ["fpsOverlay", "graphValidator"],
    "theme": "darkglass"
  }
}
```

### Potential Schema Additions (Backward-Compatible)

- `priority` (number) – ordering when multiple adapters of same role exist.
- `scope` (string) – limit adapter to a graph id / domain.
- `conflictsWith` (array&lt;string&gt;) – explicit mutual exclusion.
- `selectStrategy` (enum: first|highestPriority|chain) – resolution policy.
- `version` (string) – adapter internal semantic version (vs. descriptor version).

### Safety & Stability

- Frame hooks must fail-soft (exceptions caught; log with adapter id).
- Layout engine swaps delayed until end-of-frame barrier.
- Hot reload gating: skip replacement if currently executing adapter frame (avoid mid-call replacement).

### Exported Overlay Pack Structure (Draft)

```text
packs/
  user-overrides/
    FeatureSet.json            # references base packs + declares blocklist / adapter choices
    adapters/
      CustomBlockRenderer.cpp  # (optional RCC++ sources)
      CustomLayoutEngine.cpp
```

### Open Questions

- Do we need dependency cycles detection across adapters early? (Likely yes before Phase 6.)
- Should layouts be able to declare required frame hooks (e.g., link routing pass)?
- Provide a dry-run mode for export verifying deterministic reproduction?

### Initial Success Criteria

| Milestone | Accept Criteria |
|-----------|-----------------|
| Phase 2 | Scan logs list all adapter ids grouped by role with zero crashes |
| Phase 3 | Selecting an alternate layout engine changes block positions deterministically |
| Phase 4 | UI persists selection across restart |
| Phase 5 | Exported user pack replays same adapter set on clean launch |
| Phase 6 | Modifying a frame hook source re-injects behavior without restart |

---
This section is descriptive only; no core commitments until phases are scheduled.
