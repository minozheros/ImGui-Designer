### Development & Assistant Rules (Canonical Source)

> Rule Levels: `MUST` (hard requirement), `SHOULD` (strong recommendation—justify deviations), `MAY` (advisory). Each rule has an ID: PREFIX-NN. Reference IDs in commits & reviews.
> Machine-readable derivative: `.github/instructions/rules.yml` (non-canonical). Always update BOTH when changing rules here. Tooling/automation should treat the YAML as a generated mirror; this Markdown remains the single source of truth.
> Sync guard: `scripts/validate_rules_sync.py` (CMake target `validate_rules`) runs each build (toggle with `IMGUIDESIGNER_VALIDATE_RULES_ON_BUILD`) to detect drift between this file and the YAML mirror.
> Regeneration: run `scripts/generate_rules_yaml.py` (or CMake target `generate_rules_yaml` if enabled) to rebuild the YAML mirror (schema v2: includes `short_title`). Always edit this Markdown first; then regenerate. Optional CMake toggles: `IMGUIDESIGNER_GENERATE_RULES_TARGET` (adds target, ON by default) and `IMGUIDESIGNER_GENERATE_RULES_ON_BUILD` (auto-regenerate before validation/build, OFF by default).

**Cheat Sheet (Top 15 Critical MUST Rules)**

1. [META-01][MUST] Reread this file every 3 edits or before starting a feature/refactor.
2. [ARCH-01][MUST] All UI logic lives in classes with `render()/update()`; no free-form ImGui in `main.cpp`.
3. [GEN-01][MUST] Never hand-edit anything under `src/generated/`; regenerate via scripts.
4. [CMK-01][MUST] Use CMake only; never invoke `make` directly.
5. [OWN-01][MUST] No raw owning pointers; use RAII (`unique_ptr` default, `shared_ptr` only with clear shared lifetime).
6. [LANG-01][MUST] Use modern C++23 features where they simplify or clarify (ranges, `std::expected`, `string_view`, `span`).
7. [LOG-01][MUST] Logging inside hot loops = `debug` or lower unless failure-critical.
8. [ERR-01][MUST] Use structured error channels (`expected`/status) over sentinel return codes.
9. [NAM-01][MUST] Naming conventions: Files & classes PascalCase; funcs/vars camelCase; constants/macros UPPER_SNAKE_CASE.
10. [REV-01][MUST] Split functions > ~60 lines unless linear & cohesive.
11. [COMMIT-01][MUST] Prepare commit message in `.dev/markers/commit_message.txt` before committing.
12. [MARK-01][MUST] Generator markers live only in `.dev/markers/`; touch after successful generation.
13. [TEST-01][MUST] Update/add tests when changing behavior (schemas, node mapping, generation logic).
14. [CONSIST-01][MUST] If a rule changes, update this file in same commit.
15. [CLEAN-01][MUST] Remove dead/commented-out code promptly; don’t accumulate clutter.

Consult appendix + section 7.1 for extended facilities and advisory style.

> This file is the single canonical rule set. Other docs (e.g. `docs/Notes.md`, `README.md`) may reference or summarize but MUST NOT drift. When in doubt, defer to this file.

---

## 1. Meta & Rule Compliance

- [META-01][MUST] Always reread this file plus any explicit policy doc after every 3 file edits OR before starting a new feature/refactor.
- [META-02][SHOULD] When unclear: make a brief explicit assumption OR ask a focused question if risk of rework is high.
- [META-03][MUST] Promote recurring tacit practices here—no hidden tribal knowledge.

### 1.1 Scope Boundaries

- [SCOPE-01][MUST] No new external services/dependencies without rationale & documentation.
- [SCOPE-02][SHOULD] Avoid speculative abstraction; refactor when duplication or churn appears.

---

## 2. Architecture & Encapsulation

- [ARCH-01][MUST] UI/component logic lives in dedicated classes with `render()/update()`; no free-form ImGui in globals / `main.cpp`.
- [GEN-01][MUST] Generated artifacts reside only under `src/generated/`; modify generators, not outputs.
- [ARCH-02][SHOULD] Single Responsibility per class; split when concerns diverge (e.g., UI vs persistence).

---

## 3. Commit & Marker Workflow

### 3.1 Commit Message Flow

- [COMMIT-01][MUST] Prepare commit message in `.dev/markers/commit_message.txt` (overwrite each time) before committing.
- [COMMIT-02][MUST] Use imperative scoped prefixes: `feat:`, `fix:`, `docs:`, `refactor:`, `chore:`, `perf:`, `test:`, `build:`, `ci:`.
- [COMMIT-03][SHOULD] Split multi-topic changes unless atomic by necessity.
- [COMMIT-04][MUST] Use `git commit -F .dev/markers/commit_message.txt`.

### 3.2 Marker Directory

- [MARK-01][MUST] All sentinel markers live in `.dev/markers/`.
- [MARK-02][MUST] Naming pattern: `<feature>_<artifact>_generated.ok`.
- [MARK-03][MUST] Touch marker only after successful generation sequence.
- [MARK-04][MAY] Add new markers sparingly; prefer leveraging existing ones.

### 3.3 Adding a New Marker

1. [MARK-05][SHOULD] Extend generator CMake; reference `MARKER_DIR`.
2. [MARK-06][MUST] Add custom command producing outputs + `touch` marker.
3. [MARK-07][SHOULD] Add dependent custom target if other targets rely on outputs.
4. [MARK-08][MUST] Register marker for clean removal if appropriate.

---

## 4. Code Quality & Review Checklist

Before finalizing an edit ensure:

Structure & Includes:

- [INC-01][MUST] Group includes first; minimal, no circular band-aid includes.
- [CLEAN-01][MUST] Remove dead / commented-out code immediately.

Naming & Consistency:

- [NAM-01][MUST] Filenames & class names PascalCase.
- [NAM-02][MUST] Functions & variables camelCase.
- [NAM-03][MUST] Macros & constants UPPER_SNAKE_CASE.
- [NAM-04][SHOULD] Consistent acronym casing (e.g., `HttpClient`).

Modern C++ Practices:

- [OWN-01][MUST] RAII + smart pointers; avoid raw owning `new/delete`.
- [ENUM-01][MUST] Use `enum class`.
- [CONST-01][SHOULD] Apply `constexpr` / `const` pervasively where stable & beneficial.
- [VIRT-01][MUST] Mark overrides `override`; use `final` when no further derivation intended.

Refactoring / Maintainability:

- [REV-01][MUST] Split large functions (> ~60 lines) unless cohesive & linear.
- [REV-02][MUST] Remove duplication—extract helper or template.

Robustness & Diagnostics:

- [LOG-01][MUST] Loop logging = `debug` or lower unless failure-critical.
- [CTRL-01][SHOULD] Favor early returns over deep nesting.
- [ERR-01][MUST] Use `expected`/documented error channels over sentinel codes.

Testing & Validation:

- [TEST-01][MUST] Update/add tests for behavior changes (mapping, schemas, generation).
- [TEST-02][MUST] Update golden tests intentionally only—never via incidental regen.

Documentation Alignment:

- [CONSIST-01][MUST] Update this file in same commit when rule changes.
- [DOC-01][SHOULD] Other docs summarize & link back—no divergence.

---

## 5. Proactive Action Principles

- [ACT-01][MUST] Perform obvious follow-ups (rebuild, regenerate) without prompting.
- [ACT-02][MUST] Inspect `build/build.log` on build failure; no guessing.
- [ACT-03][SHOULD] Don’t delegate steps you can execute locally.

---

## 6. Communication Protocol

- [COMMS-01][MUST] Concise, actionable responses—no fluff.
- [COMMS-02][MUST] Admit uncertainty explicitly + next info to gather.
- [COMMS-03][SHOULD] Offer ≤3 relevant follow-up suggestions.
- [COMMS-04][MUST] Do not mention being an AI.

---

## 7. Coding Standards (Mandatory Core)

Build & Layout:

- [CMK-01][MUST] CMake only; never call `make` directly.
- [CMK-02][MUST] `.cpp` under `src/` auto-included—no manual list edits.

Header / Source Separation:

- [HDR-01][MUST] Put non-trivial logic in `.cpp`; headers: declarations, trivial inline, templates only.

Language / Library Usage:

- [LANG-01][SHOULD] Use C++23 features that clarify intent (ranges, `expected`, `string_view`, `span`).
- [LIB-01][MUST] Primary libs: ImGui, ImPlot, spdlog, fmt, nlohmann::json, EnTT, Catch2, RCC++ (introduce others only per SCOPE-01).

Idioms & Patterns:

- [PAT-01][SHOULD] Favor composition; inheritance only when polymorphism is needed.
- [OWN-02][MUST] Express ownership explicitly; prefer `unique_ptr` over `shared_ptr` unless shared semantics required.
- [VIEW-01][MUST] Use `string_view` / `span` for non-owning views with safe lifetimes.

Selected Allowed Utilities:

- [UTIL-01][SHOULD] Prefer `variant`, `optional`, `filesystem`, `format`, `ranges` where they simplify code.

Disallowed / Discouraged Without Rationale:

- [OWN-03][MUST] No raw owning pointers / manual memory management.
- [STATE-01][SHOULD] Avoid global mutable singletons (registries excepted).
- [MACRO-01][SHOULD] Avoid macro overuse for logic substitution.

Extended Reference: (See appendix + section 7.1 summary.)

- [NAM-05][SHOULD] Maintain singular/plural naming clarity.
- [REN-01][MUST] Rename file when class name changes; keep sync.
- [REN-02][MUST] Update all references when symbol name changes.
- [CONST-02][SHOULD] Use `static`, `inline`, and `constexpr` appropriately.
- [VIRT-02][MUST] Correct access specifier usage—encapsulate internals.
- [ASK-01][MUST] Clarify genuinely ambiguous requirements before implementing risky assumptions.
- [FIX-01][MUST] Investigate & fix surfaced issues or document limitation.
- [SCOPE-03][MUST] Decline out-of-scope / policy-violating requests politely with rationale.
- [REV-03][SHOULD] Break up classes accruing multiple responsibilities.
- [REV-04][SHOULD] Refactor overly long / complex functions.
- [CLAR-01][SHOULD] Improve readability when code is hard to parse.
- [QUAL-01][MUST] Align with modern C++ best practices (see 7.1 core summary + appendix).
- [STYLE-01][MUST] Match project conventions before adding new style patterns.
- [PERF-01][SHOULD] Optimize only after measuring; eliminate pathological inefficiencies.
- [SEC-01][SHOULD] Elevate safety/security concerns (bounds, lifetime, ownership) proactively.
- [MEM-01][MUST] Resolve improper memory handling (ownership leaks, dangling, races).
- [THREAD-01][MUST] Ensure thread safety for shared mutable state or confine state.
- [ERR-02][SHOULD] Strengthen error handling paths for robustness.
- [LOG-02][SHOULD] Improve logging clarity if diagnostics are poor.
- [TEST-03][SHOULD] Expand tests where coverage is weak in touched areas.
- [DOC-02][SHOULD] Improve inline/docs clarity when modifying complex logic.
- [VCS-01][SHOULD] Keep commit history clean—avoid unrelated changes in same commit.
- [DEPLOY-01][SHOULD] Preserve deploy/runtime stability; avoid breaking scripts inadvertently.
- [IMPROVE-01][MUST] Leave code at least slightly better than you found it.

---

### 7.1 Extended Modern C++ Checklist (Moved)

The extended enumerative Modern C++ facility checklist has been moved to `docs/ModernCppChecklist.md` to keep this file concise.

Rationale:

- Reduces noise for day-to-day rule scanning.
- Keeps advisory (non-binding) guidance separate from enforceable rules.
- Enables future versioning and pruning without churn in the canonical instructions.

When reviewing or refactoring, consult the appendix:
`docs/ModernCppChecklist.md`

If adding new items, update the appendix and (only if enforceable) summarize the principle here.

Enforceable Core Summary (must follow unless justified in commit message):

- Prefer standard library facilities over custom re‑implementations (algorithms, containers, smart pointers, `<chrono>`, `<filesystem>`, `<ranges>`).
- Use RAII and smart pointers (`std::unique_ptr` by default; `std::shared_ptr` only with clear shared ownership). No raw owning pointers.
- Use `enum class`, `constexpr` / `consteval`, and `override` consistently; mark intentionally non-inheritable types `final`.
- Avoid manual memory management, C-style arrays, and `new`/`delete` in application code (allowed inside clearly isolated low-level utility if unavoidable).
- Use `std::optional` for nullable semantics and `std::variant` (or domain types) instead of parallel flag/value patterns.
- Use `std::expected` (or equivalent status type) for recoverable errors; exceptions only for unrecoverable failures.
- Prefer range-based for loops and standard/ranges algorithms over handwritten index loops when readability is equal or better.
- Use `std::string_view` / `std::span` for non-owning views instead of raw pointer + length pairs.
- Pre-size / reserve containers when size is known to avoid avoidable reallocations.
- Avoid premature optimization: measure before introducing complexity (SIMD, custom allocators, manual pooling, etc.).
- Keep functions focused (single responsibility) and avoid deeply nested control flow—favor early returns.
- Prefer clear intent over clever constructs (readability > terseness).

---

## 8. Change Management & History Hygiene

- [HIST-01][MUST] Keep commits small & single-purpose.
- [HIST-02][MUST] Avoid breaking functionality unless refactor scope explicitly allows.
- [HIST-03][SHOULD] Use `docs/Notes.md` for historical/architectural rationale only—rules stay here.

---

## 9. Contextual File Selection

- [CTX-01][SHOULD] Select the most relevant file autonomously when low risk of divergence.
- [CTX-02][SHOULD] Ask only when multiple plausible targets materially diverge.
- [CTX-03][MUST] Offer alternative approaches when trade-offs are meaningful.

---

## 10. Logging

- [LOG-03][MUST] Central log: `build/ImGui-Designer.log` captures all levels.
- [LOG-04][MUST] Dedup via `src/core/helpers/init/spdlog_dedup.hpp`; do not reimplement filtering.
- [LOG-01][MUST] Loop-intensive logs <= debug unless failure-critical (already defined above; reaffirmed).

---

## 11. Generated Files Policy

- [GEN-02][MUST] Do not hand-edit generated headers under `src/generated/`.
- [GEN-03][MUST] Modify scripts in `scripts/` then regenerate.
- [GEN-04][SHOULD] Clean stale artifacts (`clean_generated`) before regen if drift suspected.

---

## 12. Recommended Defaults & Expansion (Advisory)

These are advisory; deviations require rationale in commit message or `docs/Notes.md`.

---

## 13. Appendix: Advisory Expansion Guidance

Use these as _house style_. When proposing alternatives, state trade-offs succinctly.

1. Codegen templating (packs)

- Default: Logic-less templates in packs (Mustache-style). They’re easy to learn, review, and fork—ideal for community packs.
- If native C++ templating is needed: prefer Inja (C++/header-only, integrates with nlohmann::json we already use). Alternative: mstch/kainjow::mustache. Avoid hand-built string concatenation for anything non-trivial.
- Contracts: Keep templates small and composable; pass explicit data models, not raw app types. Enforce output style via templates, not hard-coded in C++.

2. Pack install strategy (deterministic and reusable)

- Default: Hybrid mode
  - Project-local materialization (for reproducibility) + global content-addressed cache per XDG (
    ~/.cache/imgui-designer/packs/<owner>/<repo>/<ref>/<sha256>/).
  - Materialize via symlink by default; fall back to copy on unsupported FS.
- CI: Always materialize locally from cache and verify sha256; avoid global installs.

3. Native downloader (future C++)

- Keep Python fetcher as the reference path for now (simple, battle-tested in CI).
- If/when adding C++ HTTP:
  - HTTP: libcurl (widely used) or cpr (thin C++ wrapper around libcurl). Pin versions.
  - Archive: minizip or libzip. Verify sha256 before extraction; sanitize paths.
  - Hashing: use a small, portable SHA-256 (e.g., bundled) or OpenSSL if already present.
  - Always validate against index pin (ref + sha256) before accept.

4. Schema evolution and validation

- Keep $schema on all manifests; validate in CI (jsonschema).
- Favor additive, backward-compatible changes; deprecate instead of breaking.
- Encode capabilities (e.g., codegen.cxx, symbols.class) so packs can declare requirements.

5. Security and trust

- Default sources via curated indexes only; require pinned refs for official/verified packs and enforce sha256.
- Treat system/global locations as read-only data sources; never auto-elevate or write outside project without explicit user action.

6. Library selection guidance

- Prefer: widely-used, permissive license (MIT/BSD/Apache-2.0), minimal transitive deps, active maintenance.
- Existing stack: fmt, spdlog, nlohmann::json, EnTT, Catch2, ImGui/ImPlot/imgui-node-editor—stick with these unless a clear benefit.
- New deps: document rationale, alternatives, and removal plan if abandoned upstream.

7. Testing codegen and packs

- Golden tests for codegen output (Catch2): compare generated files to checked-in fixtures.
- Validate manifests and lockfiles in CI for all PRs; fail on drift or missing pins.

8. First-run behavior

- If no packs installed: prompt to install the official Standard Core pack; otherwise focus Toolbar by default. Never auto-switch tabs after startup.
