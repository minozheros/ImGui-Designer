
# Third-Party Libraries Used in uLaunch

This project uses the following libraries, most of which are integrated using CMake's FetchContent module:

- [ImGui](https://github.com/ocornut/imgui) (FetchContent)
- [SDL3](https://github.com/libsdl-org/SDL) (FetchContent)
- [SDL_image](https://github.com/libsdl-org/SDL_image) (FetchContent)
- [magic_enum](https://github.com/Neargye/magic_enum) (FetchContent)
- [fmt](https://github.com/fmtlib/fmt) (FetchContent)
- [spdlog](https://github.com/gabime/spdlog) (FetchContent)
- [stb](https://github.com/nothings/stb) (FetchContent, header-only)
- [libgpiod](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/) (system package, found via pkg-config)
- FMOD (proprietary, must be installed manually)

Integration notes:
- Most libraries are automatically downloaded and built with FetchContent.
- libgpiod must be installed on your system (e.g., via your package manager).
- FMOD must be downloaded and installed manually from https://www.fmod.com/download.

See the project's `CMakeLists.txt` for details on how each library is integrated.
