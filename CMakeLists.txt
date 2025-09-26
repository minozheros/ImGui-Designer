

cmake_minimum_required(VERSION 3.11)
project(ImGui-Designer LANGUAGES CXX)

# Centralize marker directory & helpers
include(cmake/Markers.cmake)

# Warn users about proper CMake usage
if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR AND NOT CMAKE_DISABLE_SOURCE_CHANGES)
    message(WARNING
        "\nPlease use CMake to configure and build this project.\n"
        "Do NOT run 'make' directly from the source directory.\n\n"
        "Recommended workflow:\n"
        "  mkdir build && cd build\n"
        "  cmake ..\n"
        "  make\n\n"
        "Or use the provided build script:\n"
        "  ./build.sh\n\n"
        "Or use CMake's portable build command:\n"
        "  cmake --build build\n"
    )
endif()

set(CMAKE_CXX_STANDARD 23)

option(IMGUIDESIGNER_ENABLE_TESTS "Enable building tests (Catch2)" OFF)

# Enable testing (optional)
if(IMGUIDESIGNER_ENABLE_TESTS)
    include(CTest)
    enable_testing()
endif()

include(cmake/StandardProjectSettings.cmake)
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# --- Packs (FeatureSets/Packages/Tutorials) fetch integration ---
option(IMGUIDESIGNER_FETCH_STANDARD_PACKS "Fetch standard packs from registry/packs.example.json" OFF)
include(cmake/PackFetch.cmake)
if(IMGUIDESIGNER_FETCH_STANDARD_PACKS)
    add_pack_fetch_target(fetch_packs "${CMAKE_SOURCE_DIR}/registry/packs.example.json")
endif()
option(IMGUIDESIGNER_FETCH_OFFICIAL_PACKS "Fetch official packs from registry/packs.official.json" OFF)
if(IMGUIDESIGNER_FETCH_OFFICIAL_PACKS)
    add_pack_fetch_target(fetch_official_packs "${CMAKE_SOURCE_DIR}/registry/packs.official.json")
endif()
include(cmake/ManifestValidation.cmake)
option(IMGUIDESIGNER_VALIDATE_ON_BUILD "Run manifest validation as part of build" ON)



# =============================
# Dependency Management
# =============================
include(FetchContent)

# --- Core Libraries ---

# nlohmann/json for preferences
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# EnTT for event handling
FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG        v3.15.0
)
FetchContent_MakeAvailable(entt)

# --- Testing (optional) ---
if(IMGUIDESIGNER_ENABLE_TESTS)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.10.0
    )
    FetchContent_MakeAvailable(Catch2)
endif()

# magic_enum
FetchContent_Declare(
 magic_enum
 GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
 GIT_TAG        master
)
FetchContent_MakeAvailable(magic_enum)

# fmt
FetchContent_Declare(
 fmt
 GIT_REPOSITORY https://github.com/fmtlib/fmt.git
 GIT_TAG        11.2.0
)
FetchContent_MakeAvailable(fmt)

# spdlog
FetchContent_Declare(
 spdlog
 GIT_REPOSITORY https://github.com/gabime/spdlog.git
 GIT_TAG        v1.15.3
)
FetchContent_MakeAvailable(spdlog)

# libgpiod
FetchContent_Declare(
    gpiod
    GIT_REPOSITORY https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(gpiod)

# stb (header-only, can be added as subdirectory or included directly)
FetchContent_Declare(
 stb
 GIT_REPOSITORY https://github.com/nothings/stb.git
 GIT_TAG        master
)
FetchContent_MakeAvailable(stb)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})


# --- SDL & Graphics ---
## SDL3 selection: prefer system SDL3 unless explicitly forced; provide a 'safe ALSA-only' preset for bundled SDL.
option(IMGUIDESIGNER_USE_BUNDLED_SDL3 "Force using bundled SDL3 instead of system SDL3" OFF)
option(IMGUIDESIGNER_SDL_SAFE_ALSA_ONLY "Preset: ALSA-only with PipeWire disabled for bundled SDL3" OFF)
## When fetching SDL3, disable PipeWire backend to avoid build breakage with certain PipeWire headers.
option(IMGUIDESIGNER_DISABLE_SDL_PIPEWIRE "Disable SDL3 PipeWire backend when building bundled SDL3" OFF)
option(IMGUIDESIGNER_SDL_ALSA_ONLY "When building bundled SDL3, prefer ALSA and disable other audio backends (PulseAudio, JACK, SNDIO, OSS)" OFF)

# Apply preset if requested
if(IMGUIDESIGNER_SDL_SAFE_ALSA_ONLY)
    set(IMGUIDESIGNER_DISABLE_SDL_PIPEWIRE ON CACHE BOOL "" FORCE)
    set(IMGUIDESIGNER_SDL_ALSA_ONLY ON CACHE BOOL "" FORCE)
endif()

set(USE_FETCHED_SDL3 OFF)
if(NOT IMGUIDESIGNER_USE_BUNDLED_SDL3)
    find_package(SDL3 CONFIG QUIET)
endif()
if(IMGUIDESIGNER_USE_BUNDLED_SDL3 OR NOT SDL3_FOUND)
    include(FindPkgConfig)
    pkg_check_modules(SDL3 QUIET sdl3)
    if(SDL3_FOUND)
        # Create an imported target SDL3::SDL3 from pkg-config values
        add_library(SDL3::SDL3 INTERFACE IMPORTED)
        target_include_directories(SDL3::SDL3 INTERFACE ${SDL3_INCLUDE_DIRS})
        target_link_libraries(SDL3::SDL3 INTERFACE ${SDL3_LINK_LIBRARIES})
    else()
        # Fallback to fetching SDL3
        FetchContent_Declare(
            SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG        release-3.2.0 # keep pinned to a known-good tag
        )
        # Apply SDL3 configuration knobs BEFORE making it available
        if(IMGUIDESIGNER_DISABLE_SDL_PIPEWIRE)
            # Turn off PipeWire backends in the SDL3 subbuild to avoid API mismatches on some distros
            set(SDL_PIPEWIRE OFF CACHE BOOL "Disable PipeWire backend in SDL3" FORCE)
            set(SDL_PIPEWIRE_SHARED OFF CACHE BOOL "Disable shared PipeWire in SDL3" FORCE)
        endif()
        if(IMGUIDESIGNER_SDL_ALSA_ONLY)
            # Force ALSA on and other audio backends off for a leaner, ALSA-focused build
            set(SDL_ALSA ON CACHE BOOL "Enable ALSA backend in SDL3" FORCE)
            set(SDL_ALSA_SHARED ON CACHE BOOL "Enable ALSA shared in SDL3" FORCE)
            set(SDL_PULSEAUDIO OFF CACHE BOOL "Disable PulseAudio backend in SDL3" FORCE)
            set(SDL_PULSEAUDIO_SHARED OFF CACHE BOOL "Disable PulseAudio shared in SDL3" FORCE)
            set(SDL_JACK OFF CACHE BOOL "Disable JACK backend in SDL3" FORCE)
            set(SDL_JACK_SHARED OFF CACHE BOOL "Disable JACK shared in SDL3" FORCE)
            set(SDL_SNDIO OFF CACHE BOOL "Disable SNDIO backend in SDL3" FORCE)
            set(SDL_SNDIO_SHARED OFF CACHE BOOL "Disable SNDIO shared in SDL3" FORCE)
            set(SDL_OSS OFF CACHE BOOL "Disable OSS backend in SDL3" FORCE)
        endif()
        # We do not need to install SDL when used as a subproject
        set(SDL_INSTALL OFF CACHE BOOL "Disable SDL3 install step" FORCE)
        FetchContent_MakeAvailable(SDL3)
        set(USE_FETCHED_SDL3 ON)
    endif()
endif()

find_package(OpenGL REQUIRED)



# --- RCC++ (RuntimeCompiledCPlusPlus) ---
FetchContent_Declare(
    RCCPP
    GIT_REPOSITORY https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus.git
    GIT_TAG        master # or a specific tag/commit
)
FetchContent_MakeAvailable(RCCPP)
set(RCCPP_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/rccpp-src/Aurora")


# Add RCC++ libraries manually (recursive, including subfolders)
file(GLOB_RECURSE RCCPP_RUNTIMEOBJECTSYSTEM_SRC
    "${RCCPP_SOURCE_DIR}/RuntimeObjectSystem/*.cpp"
)
file(GLOB_RECURSE RCCPP_RUNTIMECOMPILER_SRC
    "${RCCPP_SOURCE_DIR}/RuntimeCompiler/**/*.cpp"
    "${RCCPP_SOURCE_DIR}/RuntimeCompiler/*.cpp"
)
add_library(rccpp_RuntimeObjectSystem STATIC ${RCCPP_RUNTIMEOBJECTSYSTEM_SRC})
target_include_directories(rccpp_RuntimeObjectSystem PUBLIC "${RCCPP_SOURCE_DIR}/RuntimeObjectSystem")
target_link_libraries(rccpp_RuntimeObjectSystem PUBLIC rccpp_RuntimeCompiler)
add_library(rccpp_RuntimeCompiler STATIC ${RCCPP_RUNTIMECOMPILER_SRC})
target_include_directories(rccpp_RuntimeCompiler PUBLIC "${RCCPP_SOURCE_DIR}/RuntimeCompiler")


# =============================
# Local/Third-Party Subdirectories
# =============================
# FMOD is now included as a subdirectory in third_party/fmod
add_subdirectory(third_party/fmod third_party/fmod_build)
# ImGui is now included as a subdirectory in third_party/imgui
add_subdirectory(third_party/imgui third_party/imgui_build)
# ImPlot is now included as a subdirectory in third_party/implot
add_subdirectory(third_party/implot)
# imgui-node-editor is now included as a subdirectory in third_party/imgui-node-editor
add_subdirectory(third_party/imgui-node-editor)


# =============================
# Source Files & Executables
# =============================
# =============================
# Source Files & Executables
# =============================
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
if(IMGUIDESIGNER_ENABLE_TESTS)
    file(GLOB TEST_SOURCES tests/test_*.cpp)
endif()


add_executable(ImGui-Designer
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${SRC_FILES}
)

if(IMGUIDESIGNER_ENABLE_TESTS)
    add_executable(ImGui-Designer_tests
        ${TEST_SOURCES}
        ${SRC_FILES}   
    )
endif()

# =============================
# Shared Include Directories
# =============================
add_library(ImGui-Designer_includes INTERFACE)
target_include_directories(ImGui-Designer_includes INTERFACE
    ${RCCPP_SOURCE_DIR}/include
    ${RCCPP_SOURCE_DIR}/RuntimeObjectSystem
    ${RCCPP_SOURCE_DIR}/RuntimeObjectSystem/ObjectFactorySystem
    ${RCCPP_SOURCE_DIR}/RuntimeObjectSystem/SimpleSerializer
    ${RCCPP_SOURCE_DIR}/RuntimeCompiler
    ${RCCPP_SOURCE_DIR}/RuntimeCompiler/SimpleFileWatcher
    ${RCCPP_SOURCE_DIR}/Common
    ${entt_SOURCE_DIR}/src
    ${magic_enum_SOURCE_DIR}/include/magic_enum
    ${nlohmann_json_SOURCE_DIR}/include
    ${fmod_SOURCE_DIR}/api/core/include
    ${fmt_SOURCE_DIR}/include
    ${gpiod_SOURCE_DIR}/include
    # SDL3 include directories
    $<$<BOOL:${USE_FETCHED_SDL3}>:${SDL3_SOURCE_DIR}/include>
    $<$<NOT:$<BOOL:${USE_FETCHED_SDL3}>>:${SDL3_INCLUDE_DIRS}>
    ${imgui_SOURCE_DIR}
    ${OpenGL_INCLUDE_DIR}
    ${spdlog_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
    ${RCCPP_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core/types
    ${implot_SOURCE_DIR}
    ${imguinodeeditor_SOURCE_DIR}
)

target_link_libraries(ImGui-Designer PRIVATE ImGui-Designer_includes)
if(IMGUIDESIGNER_ENABLE_TESTS)
    target_link_libraries(ImGui-Designer_tests PRIVATE ImGui-Designer_includes)
endif()

set_target_properties(ImGui-Designer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


# =============================
# Post-Build Steps
# =============================
set(POSTBUILD_TARGET ImGui-Designer)
include(cmake/PostBuild.cmake)

# =============================
# Link Libraries
# =============================

target_link_libraries(ImGui-Designer PRIVATE
    EnTT::EnTT
    OpenGL::GL
    fmod
    fmt::fmt
    gpiod
    SDL3::SDL3
    imgui
    magic_enum::magic_enum
    nlohmann_json::nlohmann_json
    rccpp_RuntimeCompiler
    rccpp_RuntimeObjectSystem
    spdlog::spdlog
    stb
    implot
    imguinodeeditor
)


if(IMGUIDESIGNER_ENABLE_TESTS)
    target_link_libraries(ImGui-Designer_tests PRIVATE
        Catch2::Catch2WithMain
        EnTT::EnTT
        OpenGL::GL
        fmod
        fmt::fmt
        gpiod
        SDL3::SDL3
        imgui
        magic_enum::magic_enum
        nlohmann_json::nlohmann_json
        rccpp_RuntimeCompiler
        rccpp_RuntimeObjectSystem
        spdlog::spdlog
        stb
        implot
        imguinodeeditor
    )
endif()


# =============================
# Testing Integration
# =============================
if(IMGUIDESIGNER_ENABLE_TESTS)
    include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
    catch_discover_tests(ImGui-Designer_tests)
endif()

# =============================
# Code Generators (auto-include all in cmake/generators)
# =============================
#
# All .cmake files placed in cmake/generators/ will be automatically included here.
# This allows you to add new code generation or preprocessing steps simply by
# adding a new .cmake file to that directory. Each generator file should define
# its own custom targets, commands, or logic as needed.
#
# Example: To add a new generator, create cmake/generators/GenerateFoo.cmake
# and it will be picked up automatically on the next CMake configure.
#
file(GLOB GENERATOR_SCRIPTS "${CMAKE_SOURCE_DIR}/cmake/generators/*.cmake")
foreach(GEN_SCRIPT ${GENERATOR_SCRIPTS})
    include(${GEN_SCRIPT})
endforeach()

if(IMGUIDESIGNER_VALIDATE_ON_BUILD)
    add_dependencies(ImGui-Designer validate_manifests)
    if(IMGUIDESIGNER_ENABLE_TESTS)
        add_dependencies(ImGui-Designer_tests validate_manifests)
    endif()
endif()

# When tests are enabled, make them depend on the generator targets as well.
if(IMGUIDESIGNER_ENABLE_TESTS)
    if(TARGET ImGui-Designer_tests)
        if(TARGET imgui_api_info)
            add_dependencies(ImGui-Designer_tests imgui_api_info)
        endif()
        if(TARGET imgui_param_structs)
            add_dependencies(ImGui-Designer_tests imgui_param_structs)
        endif()
        if(TARGET node_factory_map)
            add_dependencies(ImGui-Designer_tests node_factory_map)
        endif()
        if(TARGET node_params_map)
            add_dependencies(ImGui-Designer_tests node_params_map)
        endif()
    endif()
endif()