### Assistant Workflow Rules (Minimal, Complete)

**⚠️ IMPORTANT: Read and understand these rules before starting any development task. Read the top comments and any embedded instructions in every file you want to edit before starting to edit it, and follow the stated rules. This includes understanding file-specific conventions, TODOs, or special handling requirements. These guidelines ensure consistent, high-quality code and proper project maintenance.**

1. **Rule Compliance:**

- Reread `.github/instructions/first.instructions.md`, `NOTES.md`, and any policy files after every 3 code/file changes, after every file edit, or before major features/refactors. Do this automatically, without extra comments.

2. **Encapsulation:**

- All UI/component logic must be in dedicated C++ classes with a clear interface and a `render()` method. No inline UI logic in window/global functions.

3. **Commit Workflow:**

- Overwrite `commit_message.txt` with a clear, up-to-date message before every commit.
- Stage and commit all changes using `git commit -F commit_message.txt`.
- Commits are made automatically only after the user acknowledges that the objective is achieved, or can be triggered manually with `!c`.

4. **Code Quality & Review:**

- Before finishing any file edit, review for:
  - Redundant/duplicate code or sections
  - All `#include` directives grouped at the very top of the file, before any namespace or code
  - All required `#include` directives for any types, functions, or macros used in the file are present (no missing includes)
  - No empty or redundant namespace blocks (e.g., `namespace foo {}`)
  - Proper function/class placement and organization
  - Consistent formatting and project style
  - Removal of obsolete code
- Remove redundancy and follow naming/folder conventions.
- All filenames must be in `PascalCase` (e.g., `MyClass.hpp`, `VisualBlockTypes.hpp`).
- All class names must be in `PascalCase` (e.g., `MyClass`, `VisualBlockTypes`).
- All function and variable names must be in `camelCase` (e.g., `myFunction`, `visualBlockTypes`).
- All constants and macros must be in `UPPER_SNAKE_CASE` (e.g., `MAX_BUFFER_SIZE`, `DEFAULT_COLOR`).
- All acronyms in names must be consistently cased (e.g., `HttpRequest`, `XMLParser`).
- Ensure proper use of singular/plural forms in names (e.g., `Item`, `Items`).
- If you change a class name, ensure the filename matches the new class name.
- If you change a function or variable name, ensure all references to it are updated.
- Ensure proper use of `const`, `constexpr`, `static`, and `inline` where applicable.
- Ensure proper use of access specifiers (`public`, `protected`, `private`) in classes.
- Ensure proper use of `override` and `final` keywords in virtual functions and classes.
- If you enoucnter a complex or ambiguous situation, seek clarification before proceeding.
- If you encounter a bug or issue, investigate and fix it if possible, or report it clearly.
- If you encounter a request that is out of scope or against policy, politely decline and explain why.
- If you encouter classes that are too large or have too many responsibilities, refactor them into smaller, more focused classes.
- If you encounter functions that are too long or complex, refactor them into smaller, more focused functions.
- If you encounter code that is hard to read or understand, refactor it for clarity and simplicity.
- If you encounter code that is not following best practices or modern C++ standards, refactor it to comply.
- If you encounter code that is not following project conventions or style, refactor it to match.
- If you encounter code that is not following performance best practices, refactor it for efficiency.
- If you encounter code that is not following security best practices, refactor it for safety.
- If you encounter code that is not following memory management best practices, refactor it for proper resource handling.
- If you encounter code that is not following threading best practices, refactor it for thread safety.
- If you encounter code that is not following error handling best practices, refactor it for robustness.
- If you encounter code that is not following logging best practices, refactor it for better diagnostics.
- If you encounter code that is not following testing best practices, refactor it for better coverage and reliability.
- If you encounter code that is not following documentation best practices, refactor it for better clarity and completeness.
- If you encounter code that is not following version control best practices, refactor it for better history and collaboration.
- If you encounter code that is not following deployment best practices, refactor it for better delivery and maintenance.
- If you encounter code that is not following any other best practices, refactor it for overall quality and excellence.

5. **Proactive Action:**

- Never ask the user to do something you can do.
- Act without prompting if the next step is obvious (e.g., rerun build after code change).
- **Build Logging Rule:** After every build attempt (successful or unsuccessful), immediately read the `build/build.log` file to identify exact compilation errors. Do not proceed with fixes based on assumptions - always work from the actual error content in the log file.

6. **Communication:**

- Prioritize accuracy, clarity, and depth.
- Never mention being an AI.
- If unsure, say “I don’t know.”
- No disclaimers, regretful language, or suggestions to look elsewhere.
- Provide three follow-up questions after each response, unless told otherwise.

7. **Coding Standards:**

- **Build System:** This project uses CMake as its build system. **Do not use `make` directly** - always use CMake commands. All build configuration, dependencies, and compilation are managed through CMakeLists.txt and related CMake files.
- All classes and non-trivial functions must be split into header (`.hpp`) and source (`.cpp`) files. Only trivial one-liners or templates may be header-only. No implementation logic in headers except for inline, trivial, or template code.
- Use C++23, modern C++ best practices, and the C++ Standard Library.
- Use ImGui, nlohmann/json, and spdlog as documented.
- Use short includes (e.g., `#include "enums/VisualBlockTypes.hpp"`).
- Follow established folder structure for enums, interfaces, and types.
- All `.cpp` files in `src/` are automatically included in the build by CMake. You do not need to manually update CMakeLists.txt when adding new source files to `src/`.
- When adding or changing code in any file, always follow the existing structure, formatting, and conventions present in that file. Do not introduce inconsistent organization, style, or layout.
- Use `std::unique_ptr` and `std::shared_ptr` for dynamic memory management. Avoid raw pointers unless absolutely necessary.
- Use `override` for all overridden virtual functions.
- Use `final` for classes that are not intended to be inherited from.
- Use `const` and `constexpr` where applicable.
- Use `enum class` instead of plain `enum` for better type safety.
- Use `nullptr` instead of `NULL` or `0` for pointer initialization.
- Use `auto` for type inference where the type is obvious from the context.
- Use range-based for loops instead of traditional for loops where applicable.
- Use `std::vector` or `std::array` instead of raw arrays.
- Use `std::string` instead of C-style strings.
- Use `std::make_unique` and `std::make_shared` for creating smart pointers.
- Use `emplace_back` instead of `push_back` when adding elements to STL containers.
- Use `std::optional` for values that may or may not be present.
- Use `std::variant` for types that can hold multiple types.
- Use `std::filesystem` for file and path operations.
- Use `std::thread` and related classes for multithreading.
- Use `std::mutex` and related classes for thread synchronization.
- Use `std::chrono` for time-related operations.
- Use `std::algorithm` functions for common operations like sorting, searching, and transforming collections.
- Use `std::tuple` for grouping multiple values of different types.
- Use `std::pair` for grouping two values of different types.
- Use `std::function` for function objects and callbacks.
- Use `std::bind` for binding function arguments.
- Use `std::accumulate` for summing or accumulating values in a collection.
- Use `std::transform` for transforming elements in a collection.
- Use `std::find_if` for finding elements in a collection based on a predicate.
- Use `std::sort` for sorting collections.
- Use `std::copy` for copying elements from one collection to another.
- Use `std::remove_if` for removing elements from a collection based on a predicate.
- Use `std::for_each` for applying a function to each element in a collection.
- Use `std::all_of`, `std::any_of`, and `std::none_of` for checking conditions on collections.
- Use `std::iota` for generating sequences of numbers.
- Use `std::shuffle` for randomizing the order of elements in a collection.
- Use `std::sample` for randomly sampling elements from a collection.
- Use `std::clamp` for clamping values within a range.
- Use `std::gcd` and `std::lcm` for computing greatest common divisors and least common multiples.
- Use `std::bitset` for managing sets of bits.
- Use `std::regex` for regular expressions.
- Use `std::any` for type-safe containers of single values of any type.
- Use `std::scoped_lock` for locking multiple mutexes.
- Use `std::jthread` for joining threads automatically when they go out of scope.
- Use `std::barrier` and `std::latch` for thread synchronization.
- Use `std::stop_token` for cooperative thread cancellation.
- Use `std::span` for non-owning views of contiguous sequences of objects.
- Use `std::mdspan` for multi-dimensional array views.
- Use `std::format` for formatting strings.
- Use `std::source_location` for capturing source code location information.
- Use `std::expected` for functions that may fail and return an error.
- Use `std::ranges` for range-based algorithms and views.
- Use `std::numbers` for mathematical constants.
- Use `std::execution` for parallel algorithms.
- Use `std::atomic` for atomic operations on shared data.
- Use `std::coroutine` for asynchronous programming.
- Use `std::literals` for user-defined literals.
- Use `std::syncstream` for synchronized output to streams.
- Use `std::pmr` for polymorphic memory resources.
- Use `std::bit` for bit manipulation utilities.
- Use `std::chrono_literals` for time literals.
- Use `std::views` for creating views of ranges.
- Use `std::to_array` for creating arrays from initializer lists.
- Use `std::to_underlying` for converting enum class values to their underlying type.
- Use `std::assume_aligned` for assuming pointer alignment.
- Use `std::is_constant_evaluated` for checking if code is being evaluated at compile time.
- Use `std::is_nothrow_move_constructible` and related type traits for checking type properties.
- Use `std::is_aggregate` for checking if a type is an aggregate.
- Use `std::is_invocable` and related type traits for checking if a callable can be invoked with certain arguments.
- Use `std::is_swappable` and related type traits for checking if a type is swappable.
- Use `std::is_trivially_copyable` and related type traits for checking if a type is trivially copyable.
- Use `std::is_standard_layout` and related type traits for checking if a type has standard layout.
- Use `std::is_volatile` and related type traits for checking if a type is volatile.
- Use `std::is_final` and related type traits for checking if a class is final.
- Use `std::is_abstract` and related type traits for checking if a class is abstract.
- Use `std::is_polymorphic` and related type traits for checking if a class is polymorphic.
- Use `std::is_empty` and related type traits for checking if a class is empty.
- Use `std::is_literal_type` and related type traits for checking if a type is a literal type.
- Use `std::is_signed` and related type traits for checking if a type is signed.
- Use `std::is_unsigned` and related type traits for checking if a type is unsigned.
- Use `std::is_integral` and related type traits for checking if a type is an integral type.
- Use `std::is_floating_point` and related type traits for checking if a type is a floating point type.
- Use `std::is_arithmetic` and related type traits for checking if a type is an arithmetic type.
- Use `std::is_enum` and related type traits for checking if a type is an enum.
- Use `std::is_class` and related type traits for checking if a type is a class.

8. **Change Management:**

- Make small, incremental code changes.
- Do not break existing functionality.
- Ensure changes are robust, maintainable, and production-ready.
- Document all design decisions and noteworthy changes in `NOTES.md`.

10. **Contextual File Selection:**

- If a file is not clearly specified in a command, but one or more files are present in the context, select the file that best matches the task. If multiple files could fit and it is ambiguous, ask the user which file to use.
- Offer multiple solutions or viewpoints when appropriate.
- Seek clarity if a question is unclear.
- Acknowledge and correct errors.

11. **Logging**

- All application logs are written to `build/ImGui-Designer.log` by default. This file contains all spdlog output, including debug, info, warning, and error messages.
- The logger is configured in `src/core/helpers/init/spdlog_dedup.hpp` to deduplicate repeated messages and log both to the console and to this file.
- Check this log for detailed runtime diagnostics, debugging, and error tracking.

12. **Generated Files**

- Do not edit manually, but edit the respective scripts to reflect the needed changes!
