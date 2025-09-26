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
- `cmake --build build --target ImGui-Designer_tests` - Build and run tests (requires `-DIMGUIDESIGNER_ENABLE_TESTS=ON` at configure time)
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

## Documentation

Additional design documents and specifications live in the `docs/` directory:

- Extensibility & Customization (`docs/EXTENSIBILITY.md`)
- Documentation Index (`docs/README.md`)
- Widgets & Node/Block Types (`docs/Nodes.md`)
- Project Notes (`docs/Notes.md`)
- Contributing Manifests (`docs/ContributingManifests.md`)

Future planned docs (placeholders in index): Packs & Distribution, Schema Evolution Policy, Runtime Compilation Architecture, Theming Guidelines.

## SDL3 selection and audio backends

The build prefers a system-installed SDL3 when available. If not found, it bundles SDL3.

- System SDL3: we do not alter its configuration; audio backends depend on your distro's SDL3 build (PipeWire, ALSA, PulseAudio, etc.).
- Bundled SDL3: configurable defaults. For a safe ALSA-only preset (recommended if you hit PipeWire header issues), use `IMGUIDESIGNER_SDL_SAFE_ALSA_ONLY=ON`, which sets:
  - IMGUIDESIGNER_DISABLE_SDL_PIPEWIRE=ON: disables PipeWire backend in the SDL subbuild.
  - IMGUIDESIGNER_SDL_ALSA_ONLY=ON: enables ALSA (+shared) and disables PulseAudio, JACK, SNDIO, and OSS.

You can override these defaults at configure time when bundling SDL3:

```bash
cmake -B build -S . \
  -DIMGUIDESIGNER_SDL_SAFE_ALSA_ONLY=ON
```

At runtime, you can force a specific audio driver for either system or bundled SDL:

```bash
export SDL_AUDIODRIVER=alsa      # force ALSA
export SDL_AUDIODRIVER=pipewire  # force PipeWire
```

Advanced:

- Force bundled vs system SDL3:

```bash
cmake -B build -S . -DIMGUIDESIGNER_USE_BUNDLED_SDL3=ON   # force bundled
cmake -B build -S . -DIMGUIDESIGNER_USE_BUNDLED_SDL3=OFF  # prefer system (default)
```


- Customize individual audio backends when bundling SDL3:

```bash
cmake -B build -S . \
  -DIMGUIDESIGNER_DISABLE_SDL_PIPEWIRE=OFF \
  -DIMGUIDESIGNER_SDL_ALSA_ONLY=OFF
```
 
## Runtime Logging Control

You can adjust log verbosity without changing the preferences file via CLI flags or an environment variable. Precedence (highest wins):

1. `--trace`
2. `--verbose` / `-v`
3. `--log-level=LEVEL`
4. `IMGDESIGNER_LOG_LEVEL` environment variable
5. Preferences value `logging.level` in the config file
6. Fallback: `info`

Supported levels: `trace, debug, info, warn, error, critical, off`.

Examples:

```bash
# Most verbose (trace)
./bin/ImGui-Designer --trace

# Debug verbosity
./bin/ImGui-Designer -v

# Explicit level
./bin/ImGui-Designer --log-level=warn

# Using environment variable
export IMGDESIGNER_LOG_LEVEL=debug
./bin/ImGui-Designer
```

Show help (also prints usage lines about logging flags):

```bash
./bin/ImGui-Designer --help
```

These controls allow temporary elevation of logging noise (e.g., when pairing with a bug report) without permanently editing configuration.

## Project Structure

See `NOTES.md` for detailed project structure and development guidelines.
