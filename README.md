# ImGui Designer

A visual creator for ImGui-based UIs using a node/block editor with live preview and C++ code generation.

**Note:** For project rules, workflow guidelines, and coding standards, see `.github/instructions/first.instructions.md`. If there is any conflicting information between this file and `first.instructions.md`, `first.instructions.md` takes precedence.

## Build Instructions

This project uses **CMake** as its build system. **Do not use `make` directly** - always use CMake commands or the provided build script.

### Quick Start (Recommended)

```bash
# Clone and setup
git clone <repository>
cd ImGui-Designer

# Build using the provided script
./build.sh

# Or build manually:
mkdir build
cd build
cmake ..
make
```

### Using the Build Script

The `build.sh` script ensures proper CMake usage and provides additional options:

```bash
# Basic build (Debug mode)
./build.sh

# Reconfigure and build (useful when CMakeLists.txt changes)
./build.sh reconfigure

# Clean, reconfigure and build
./build.sh clean reconfigure

# Release build
./build.sh release

# Regenerate all auto-generated files
./build.sh regenerate

# Clean all auto-generated files
./build.sh clean-generated

# Build with specific job count
./build.sh -j 4

# Show help
./build.sh --help
```

### Manual CMake Build

If you prefer manual control:

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build . --parallel

# Run the application
./bin/ImGui-Designer
```

### Available Build Targets

- `cmake --build build` - Build the main executable
- `cmake --build build --target ImGui-Designer_tests` - Build and run tests
- `cmake --build build --target clean_generated` - Remove all auto-generated files (also: `./build.sh clean-generated`)
- `cmake --build build --target regenerate_all` - Clean and regenerate all auto-generated files (also: `./build.sh regenerate`)
- `cmake --build build --target imgui_api_info` - Extract ImGui API information
- `cmake --build build --target imgui_param_structs` - Generate parameter structs
- `cmake --build build --target node_params_map` - Generate node parameter mappings

### VS Code Integration

If you're using VS Code with the CMake Tools extension, the workspace is pre-configured to use the build script automatically. Simply use the CMake Tools commands:

- **Build**: `Ctrl+Shift+P` → "CMake: Build"
- **Clean**: `Ctrl+Shift+P` → "CMake: Clean"
- **Debug**: `Ctrl+Shift+P` → "CMake: Debug"

#### VS Code Tasks (Recommended)

For the best experience, use VS Code's Task system which provides a clean, organized menu of build operations:

- **Tasks: Run Build Task** (`Ctrl+Shift+P`) → Select from:
  - `Build ImGui-Designer` - Standard build (default)
  - `Clean Build` - Clean and rebuild
  - `Reconfigure & Build` - Reconfigure CMake and build
  - `Full Rebuild` - Complete clean rebuild
  - `Regenerate Files` - Regenerate auto-generated files
  - `Clean Generated Files` - Clean auto-generated files

- **Tasks: Run Test Task** → `Run Tests` - Execute the test suite

These tasks use the build script under the hood, ensuring consistent behavior between command-line and VS Code usage.

The extension will automatically use `./build.sh` for building and `./build.sh clean` for cleaning, ensuring proper CMake workflow.

> **Note**: VS Code settings are configured in `.vscode/settings.json` and tasks in `.vscode/tasks.json`. If you modify the build script, the VS Code integration will automatically use your changes.
>
> **Troubleshooting**: If you encounter CMake generator conflicts (e.g., "generator : Ninja does not match the generator used previously"), run `./build.sh clean` to clean the build directory and try again.

## Features

- Visual node/block editor for ImGui UI creation
- Live preview of ImGui output
- C++ code generation from visual graphs
- Runtime compilation and hot-reload using RCC++
- Export functionality for integration into other projects

## Project Structure

See `NOTES.md` for detailed project structure and development guidelines.
