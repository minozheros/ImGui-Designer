

cmake_minimum_required(VERSION 3.11)
project(ImGui-Designer LANGUAGES CXX)

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

# Enable testing
include(CTest)
enable_testing()

include(cmake/StandardProjectSettings.cmake)
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)



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

# --- Testing ---
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.10.0
)
FetchContent_MakeAvailable(Catch2)

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
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.0 # or latest stable
)
FetchContent_MakeAvailable(SDL3)

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
file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
file(GLOB TEST_SOURCES tests/test_*.cpp)


add_executable(ImGui-Designer
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${SRC_FILES}
)

add_executable(ImGui-Designer_tests
    ${TEST_SOURCES}
    ${SRC_FILES}   
)

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
    ${SDL3_SOURCE_DIR}/include
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
target_link_libraries(ImGui-Designer_tests PRIVATE ImGui-Designer_includes)

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
    Catch2::Catch2
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


# =============================
# Testing Integration
# =============================
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
catch_discover_tests(ImGui-Designer_tests)

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