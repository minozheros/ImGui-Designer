
# Code Generators in CMake

## Code Generators in CMake

All `.cmake` files placed in `cmake/generators/` are automatically included by the main `CMakeLists.txt`.

This allows you to add new code generation or preprocessing steps simply by adding a new `.cmake` file to that directory. Each generator file should define its own custom targets, commands, or logic as needed.

**Example:**

To add a new generator, create `cmake/generators/GenerateFoo.cmake` and it will be picked up automatically on the next CMake configure.

## ImGui Designer – Project Notes

This file is for recording noteworthy information, design decisions, gotchas, and ideas as the project evolves. Use it as a memory aid and to help onboard new contributors.

---

## Project Intent

ImGui Designer is a visual creator for ImGui-based UIs. The goal is to enable users to build ImGui interfaces visually using a node/block editor, with a live preview window showing the actual ImGui output. The system generates C++ code from the visual graph and uses rccpp for on-the-fly compilation and hot-reload, allowing instant feedback and rapid prototyping. Users can export or save the generated code for integration into other projects, making ImGui Designer a powerful tool for UI development, prototyping, and code generation.

## Coding & Naming Conventions

- Use C++23 features where appropriate.
- Prefer modern C++ best practices and the C++ Standard Library.
- Use ImGui, nlohmann/json, and spdlog libraries as documented:
  - `#define IMGUI_DEFINE_MATH_OPERATORS` before `#include <imgui.h>` and `#include <imgui_internal.h>`
  - `#include <nlohmann/json.hpp>` for JSON
  - `#include <spdlog/spdlog.h>` for logging (all logging via spdlog)
- All files in `src/` and `src/core/types/` are on the include path; use short includes like `#include "enums/VisualBlockTypes.hpp"`.
- Follow established folder structure for enums, interfaces, and types.
- Files in `src/` are auto-added to CMakeLists.txt.
- Code should be well-commented and adhere to best practices.
- Make small, incremental code changes; avoid sweeping changes.
- Ensure code is efficient, secure, maintainable, and compatible with the codebase.
- Document and explain all code changes clearly.

### Naming Conventions

- **Files:** Use `snake_case` (e.g., `this_is_a_filename.txt`).
- **Classes/Structs:** Use `UpperCamelCase` (a.k.a. PascalCase), e.g., `TopDownHelper`.



## Design Decisions

-


## Gotchas & Caveats

-


## Ideas & Future Features

-


## Technical Debt / Refactoring

-


## Resources & References

-


## Quick How-Tos

-


---

Feel free to add, edit, or reorganize sections as the project grows!
