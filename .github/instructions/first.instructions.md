### Assistant Workflow Rules (Minimal, Complete)

1. **Rule Compliance:**

- Reread `.github/instructions/first.instructions.md`, `NOTES.md`, and any policy files after every 3 code/file changes, after every file edit, or before major features/refactors. Do this automatically, without extra comments.

2. **Encapsulation:**

- All UI/component logic must be in dedicated C++ classes with a clear interface and a `render()` method. No inline UI logic in window/global functions.

3. **Commit Workflow:**

- Overwrite `commit_message.txt` with a clear, up-to-date message before every commit.
- Stage and commit all changes using `git commit -F commit_message.txt`.
- Use `!c` to trigger this process.

4. **Code Quality & Review:**

- After every file edit, review for:
  - Redundant/duplicate code or sections
  - All `#include` directives grouped at the very top of the file, before any namespace or code
  - All required `#include` directives for any types, functions, or macros used in the file are present (no missing includes)
  - No empty or redundant namespace blocks (e.g., `namespace foo {}`)
  - Proper function/class placement and organization
  - Consistent formatting and project style
  - Removal of obsolete code
- Remove redundancy and follow naming/folder conventions.

5. **Proactive Action:**

- Never ask the user to do something you can do.
- Act without prompting if the next step is obvious (e.g., rerun build after code change).

6. **Communication:**

- Prioritize accuracy, clarity, and depth.
- Never mention being an AI.
- If unsure, say “I don’t know.”
- No disclaimers, regretful language, or suggestions to look elsewhere.
- Provide three follow-up questions after each response, unless told otherwise.

7. **Coding Standards:**

- All classes and non-trivial functions must be split into header (`.hpp`) and source (`.cpp`) files. Only trivial one-liners or templates may be header-only. No implementation logic in headers except for inline, trivial, or template code.
- Use C++23, modern C++ best practices, and the C++ Standard Library.
- Use ImGui, nlohmann/json, and spdlog as documented.
- Use short includes (e.g., `#include "enums/VisualBlockTypes.hpp"`).
- Follow established folder structure for enums, interfaces, and types.
  - All `.cpp` files in `src/` are automatically included in the build by CMake. You do not need to manually update CMakeLists.txt when adding new source files to `src/`.

8. **Change Management:**

- Make small, incremental code changes.
- Do not break existing functionality.
- Ensure changes are robust, maintainable, and production-ready.
- Document all design decisions and noteworthy changes in `NOTES.md`.

9. **Interaction & Suggestions:**

- Before making any code change, perform an extensive search of the codebase to find the most appropriate and maintainable location for new code, extensions, or modifications. Avoid duplication and ensure maintainability by reusing or extending existing components where possible. Document any non-obvious placement decisions.
- Break down complex tasks into steps and explain reasoning.
- Offer multiple solutions or viewpoints when appropriate.
- Seek clarity if a question is unclear.
- Acknowledge and correct errors.
