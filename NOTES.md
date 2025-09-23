# Workflow Rule: Periodic Rereading of Project Rules (added 23. September 2025)

To ensure strict compliance and avoid context drift, the assistant must reread all project rules and instructions (from `.github/instructions/first.instructions.md`, `NOTES.md`, and any other policy files) after every 3 code or file changes, or before starting any new major feature or refactor. This rereading will be handled automatically as part of the workflow, without extra comments or notifications, so the process remains seamless and unobtrusive. This guarantees that all actions remain aligned with the latest requirements and conventions.

**Rationale:**
- Prevents forgetting or drifting from project rules during long or complex sessions
- Ensures all code and workflow changes remain compliant
- Aids onboarding and consistency for all contributors

# Project Structure Overview (as of 23. September 2025)


This section documents the main directories and their intended purposes to clarify where information, code, and assets should be placed. Update as the project evolves.

## Top-Level Directories

- `src/` — Main C++ source code for the application
  - `src/main.cpp` — Application entry point
  - `src/app/` — Application-level helpers, user preferences, and configuration files
    - `preferences/` — Default and user-editable config/theme JSONs
  - `src/core/` — Core logic and reusable components
    - `components/` — Visual blocks, windows, registries, and event handlers
    - `events/` — Event system headers
    - `factories/` — Factory patterns for component creation
    - `helpers/` — Initialization, logging, and utility helpers
    - `themes/` — Theme loader and related code
    - `types/` — Enums, interfaces, and type definitions
- `tests/` — Unit and integration tests (Catch2-based)
  preferences
- `cmake/` — CMake configuration scripts and code generation logic
  - `CompilerWarnings.cmake`, `StandardProjectSettings.cmake`, etc. — Project-wide build settings
  - `generators/` — **All CMake code generators live here.**
    - Each `.cmake` file in this folder is automatically included by the main `CMakeLists.txt`.
    - Used for code generation, preprocessing, and custom build steps (e.g., ImGui API info extraction).
    - To add a new generator, simply create a new `.cmake` file in this directory.
- `scripts/` — Python and YAML scripts for code generation, validation, and automation
  - `generate_all.py` — Main entry for codegen pipeline
  - `extract_imgui_api_information.py`, `generate_blocks_yaml.py`, etc. — Specialized codegen and checks
  - `output/` — Generated JSON and coverage reports
- `fonts/` — Font files (e.g., `arial.ttf`, `Quartz.ttf`, `forkawesome-webfont.ttf`)
- `third_party/` — External dependencies (not tracked by package manager)
  - `imgui/`, `implot/`, `fmod/` — Source or CMake integration for third-party libraries
  - `README.txt` — Notes on third-party usage
- `build/` — Build output, generated binaries, and CMake artifacts
  - `bin/` — Compiled executables and runtime assets
  - `*_build/`, `*_src/`, `*_subbuild/` — CMake external project builds
  - `CMakeFiles/`, `CTestTestfile.cmake`, etc. — CMake system files

## Key Project Files

- `CMakeLists.txt` — Main CMake build configuration
- `README_NODES.md` — Documentation for node system or project-specific notes
- `NOTES.md` — Design decisions, gotchas, and project workflow notes (this file)
- `.github/instructions/first.instructions.md` — Assistant and workflow instructions
- `.gitignore` — Files and folders excluded from git
- `.clang-tidy` — Linting and static analysis configuration

## Conventions
## Implementation Philosophy
### Adding New Functionality

Before adding new functionality (code, UI, or features), always search the codebase to find the most appropriate place for it. This helps avoid duplication, ensures maintainability, and keeps related logic together. If in doubt, prefer extending or reusing existing components over creating new ones. Document any non-obvious placement decisions in this file.

### C++ Member and Include Organization

- Member variables should be declared inside the struct/class definition, grouped with related context data.
- Constructors should initialize all member variables, preferably using initializer lists.
- Getter/setter methods should be defined within the struct/class for encapsulation.
- `#include` directives for project headers should be placed after `#pragma once` in header files, following standard C++ conventions.
- Code, features, and examples should be implemented in a way that is robust, extendable, and suitable for production use—not just as minimal or illustrative demos.
- Favor solutions that are immediately usable and can be built upon as the project grows.
- Design components and data structures with future extensibility and integration in mind.

- Source code: Place new features in `src/core/` or `src/app/` as appropriate.
- Tests: Add new test files to `tests/` and register in CMake if needed.
- Scripts: Place automation/codegen scripts in `scripts/` and document usage.
- Third-party: Add new dependencies to `third_party/` and update documentation.
- Build output: All generated files and binaries go in `build/`.


## Git Commit Workflow

## Build Success Marker (Automation)

## Commit Message File Workflow

- All automated or semi-automated git commits use the file `commit_message.txt` in the project root.
- Before each commit, the assistant or user updates this file with a detailed commit message.
- The commit is then created using `git commit -F commit_message.txt`.
- This approach ensures consistent, explicit commit messages and simplifies approval in environments that require it.

- After every successful build of the main target, CMake creates a file named `build_succeeded.marker` in the build directory.
- This marker file is used by automation tools to detect when a build has completed successfully and to trigger post-build actions (such as automatic git commits).
- The marker is created by a post-build step in `cmake/PostBuild.cmake` using:
  ```cmake
  add_custom_command(
      TARGET ImGui-Designer POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/build_succeeded.marker
      COMMENT "Marking successful build"
  )
  ```

- After every successful build, a git commit is automatically created with a meaningful message summarizing the changes.
- This applies to both manual and automated edits.
- The commit message will reflect the nature of the changes (e.g., feature, fix, refactor, config update, etc.).
- This ensures every working state is restorable and all progress is tracked.
 
Add new folders or files to this list as the project evolves to keep the structure clear and maintainable.

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


## UI/Component Encapsulation Rule (added 23. September 2025)

### Rule
All ImGui UI/component logic (including panels, toolbars, search boxes, and any reusable widget) **must be encapsulated in dedicated C++ classes**. Do not place UI logic inline in window functions or in global/static functions. Each UI component should have its own class, with a clear interface and a `render()` method (or similar) for drawing its contents.

**Rationale:**
- Improves maintainability and testability
- Makes UI code modular and reusable
- Keeps window functions clean and focused on layout
- Eases onboarding for new contributors

### Minimal Example
```cpp
// src/core/components/ToolbarPanel.hpp
#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <string>
#include <vector>

class ToolbarPanel {
  std::string nodeSearch;
  char searchBuffer[128] = "";
  std::vector<std::string> allNodes;
public:
  ToolbarPanel() : allNodes{"Add", "Subtract", "Multiply"} {}
  void render() {
    if (ImGui::InputText("Search nodes", searchBuffer, IM_ARRAYSIZE(searchBuffer), ImGuiInputTextFlags_CallbackResize)) {
      nodeSearch = searchBuffer;
    }
    for (const auto& nodeName : allNodes) {
      if (nodeSearch.empty() || nodeName.find(nodeSearch) != std::string::npos) {
        if (ImGui::Button(nodeName.c_str())) {
          // Handle node selection
        }
      }
    }
  }
};
```

**Usage in window code:**
```cpp
static ToolbarPanel toolbar;
ImGui::Begin("Toolbar");
toolbar.render();
ImGui::End();
```

### Enforcement
- All new UI/component logic must follow this rule.
- Refactor legacy code as time permits.

---

---

Feel free to add, edit, or reorganize sections as the project grows!
