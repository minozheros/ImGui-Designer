# Modern C++ Appendix (Extended Checklist)

This appendix contains the extended Modern C++ reference checklist that was previously embedded directly in `.github/instructions/first.instructions.md` under section `7.1 Extended Modern C++ Checklist`.

Purpose:

- Provide a comprehensive (but non-binding) catalogue of preferred C++23 language/library facilities and patterns.
- Serve as a quick scanning reference when refactoring legacy code or reviewing PRs.
- Keep the canonical instructions file focused and scannable.

Usage Guidance:

- Treat this as advisory; do not cargo-cult. Prefer clarity over cleverness.
- When removing an item from usage due to legitimate trade-offs (portability, compile time, readability), note rationale in the PR.
- If you add a new facility recommendation, ensure it is C++20+ and widely supported in major compilers.

---

## Extended Modern C++ Checklist

Build & Structural:

- Project uses CMake; never invoke `make` directly. All `.cpp` in `src/` auto-included.
- Split non-trivial classes/functions into header + implementation (`.hpp`/`.cpp`).

Core Practices:

- Target C++23. Prefer standard library over custom utilities.
- Use ImGui, nlohmann::json, spdlog per project conventions.
- Prefer short relative includes (e.g. `#include "core/Foo.hpp"`).

Ownership & Lifetime:

- Use `std::unique_ptr` for exclusive ownership; `std::shared_ptr` only when shared lifetime is essential.
- Use `std::weak_ptr` to break cycles.
- Avoid raw owning pointers; raw pointers are non-owning observers.
- Prefer RAII for all resources.

Classes & Inheritance:

- Mark overrides with `override`; seal types with `final` when not designed for inheritance.
- Prefer composition over inheritance.
- Use `= delete` for forbidden operations; `= default` for trivial special members.

Enums & Types:

- Use `enum class` for scoped enumerations.
- Use strong typedefs / wrappers for semantically distinct primitive types if confusion likely.

Constants & Immutability:

- Use `constexpr` / `consteval` where compile-time evaluation is desired.
- Use `const` pervasively for invariant data; pass large objects by `const&`.

Initialization & Safety:

- Always initialize members in-class or in constructor member initializer list.
- Avoid uninitialized state and sentinel magic values.

Templates & Generics:

- Use constrained templates (`requires` clauses, concepts) when publishing generic utilities.
- Avoid premature templating—prefer concrete implementations first.

Functions:

- Keep functions short and focused—single responsibility.
- Use trailing return type only when readability improves (e.g. lambdas, complex templates).

Control Flow:

- Prefer early returns to deeply nested conditionals.
- Avoid exceptions for control flow; use `std::expected` (or status objects) for recoverable errors.

Standard Library Containers & Algorithms:

- Prefer `std::vector` for dynamic sequences; `std::array` for fixed-size.
- Avoid manual new/delete; avoid raw dynamic arrays.
- Use `emplace_back` for in-place construction.
- Prefer algorithms (`std::transform`, `std::find_if`, `std::ranges::...`) over hand-written loops when it improves clarity.
- Use `std::optional` for nullable semantics; no sentinel return codes.
- Use `std::variant` for tagged unions.
- Use `std::span`/`std::string_view` for non-owning views.
- Use `std::to_underlying` for enum to integral conversions.

Text & Formatting:

- Use `std::string` / `std::u8string` where appropriate; avoid C arrays.
- Use `std::format` (or `fmt`) for formatting; avoid manual string concatenation in tight loops.

Time & Chrono:

- Use `std::chrono` types for durations/time points; never raw integers for milliseconds, etc.
- Use chrono literals (`100ms`, `2s`).

Concurrency:

- Use `std::jthread` for scoped threads.
- Use `std::mutex`, `std::scoped_lock`, `std::lock_guard` for synchronization.
- Use `std::atomic` for primitive atomic operations.
- Prefer message passing / queues over shared mutable state when feasible.
- Use `std::stop_token` for cooperative cancellation.

Ranges & Views:

- Use `<ranges>` pipelines for expressive transformations when it clarifies intent.
- Prefer simple loops if a ranges pipeline would be less clear or harder to debug.

Coroutines (if/when adopted):

- Restrict to clearly asynchronous workflows; document lifetime semantics.

Errors & Diagnostics:

- Use `std::expected<T,E>` or status objects for recoverable failures.
- Throw exceptions only for truly exceptional unrecoverable conditions.
- Avoid `assert` in production paths for recoverable issues—use error handling.
- Use `std::source_location` to enrich diagnostics when helpful.

Numeric & Math:

- Use `<numbers>` for constants, avoid hard-coded literals (`std::numbers::pi`).
- Use `std::clamp` instead of manual min/max chains.

Memory & Performance:

- Avoid premature optimization; measure first.
- Use `reserve()` on vectors when size is known ahead.
- Prefer move semantics and `std::move` where ownership transfers.
- Use `std::pmr` only if profiling shows allocator pressure.

Utilities & Introspection:

- Use appropriate `<type_traits>` utilities (`std::is_trivially_copyable`, etc.) for static assertions.
- Use `constexpr` algorithms for compile-time computation when beneficial.

Parallel & Execution:

- Use execution policies (`std::execution::par`) only after measuring benefit; watch contention.

Bit & Low-Level:

- Use `<bit>` utilities (e.g., `std::bit_cast`, `std::popcount`) instead of custom implementations.

Regex / Parsing:

- Prefer lightweight parsing over regex in hot paths.

Filesystem:

- Use `std::filesystem::path` for all paths; avoid raw string concatenation.

Adoption Notes:

- Not every listed facility must appear in code—this is a menu, not a mandate.
- Remove or deprecate items if they prove harmful (complexity, portability, compile time).

Full Facility Reference (Enumerative):
`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`, `std::optional`, `std::variant`, `std::expected`, `std::ranges`, `std::span`, `std::mdspan`, `std::array`, `std::vector`, `std::string`, `std::u8string`, `std::format`, `std::source_location`, `std::thread`, `std::jthread`, `std::mutex`, `std::scoped_lock`, `std::stop_token`, `std::barrier`, `std::latch`, `std::execution`, `std::filesystem`, `std::chrono`, `std::numbers`, `std::bit`, `std::syncstream`, `std::pmr`, `std::coroutine` (when enabled), `std::to_array`, `std::to_underlying`, `std::assume_aligned`, `std::gcd`, `std::lcm`, algorithms: `std::transform`, `std::accumulate`, `std::find_if`, `std::all_of`, `std::any_of`, `std::none_of`, `std::remove_if`, `std::for_each`, `std::iota`, `std::shuffle`, `std::sample`, plus associated type traits: `std::is_invocable`, `std::is_aggregate`, `std::is_trivially_copyable`, `std::is_standard_layout`, `std::is_final`, `std::is_enum`, `std::is_arithmetic`, `std::is_integral`, `std::is_floating_point`, `std::is_polymorphic`.

Change Log:

- 2025-09-26: Migrated from instructions file to appendix.
