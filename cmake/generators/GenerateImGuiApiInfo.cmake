# Generate ImGui API Information
find_package(Python3 REQUIRED COMPONENTS Interpreter)


set(IMGUI_H_PATH "${CMAKE_SOURCE_DIR}/build/_deps/imgui-src/imgui.h")
set(API_INFO_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/scripts/output/")


add_custom_command(
    OUTPUT ${API_INFO_OUTPUT_DIR}/imgui_functions.json
           ${API_INFO_OUTPUT_DIR}/imgui_enums.json
           ${API_INFO_OUTPUT_DIR}/imgui_structs.json
           ${API_INFO_OUTPUT_DIR}/imgui_typedefs.json
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/extract_imgui_api_information.py
            ${IMGUI_H_PATH} ${API_INFO_OUTPUT_DIR}
    DEPENDS ${IMGUI_H_PATH} ${CMAKE_SOURCE_DIR}/scripts/extract_imgui_api_information.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Extracting ImGui API information from imgui.h"
)

# Add typedef value extraction step
add_custom_command(
    OUTPUT ${API_INFO_OUTPUT_DIR}/imgui_typedef_values.json
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/generators/scan_typedefs_and_collect_values.py
            ${API_INFO_OUTPUT_DIR}/imgui_typedefs.json
            ${CMAKE_BINARY_DIR}/_deps/imgui-src
            ${API_INFO_OUTPUT_DIR}/imgui_typedef_values.json
    DEPENDS ${API_INFO_OUTPUT_DIR}/imgui_typedefs.json ${CMAKE_SOURCE_DIR}/scripts/generators/scan_typedefs_and_collect_values.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Extracting ImGui typedef values from enum blocks"
)

# Add parameter type coverage check step
add_custom_command(
    OUTPUT ${API_INFO_OUTPUT_DIR}/imgui_param_type_coverage.ok
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/check_imgui_param_type_coverage.py
    COMMAND ${CMAKE_COMMAND} -E touch ${API_INFO_OUTPUT_DIR}/imgui_param_type_coverage.ok
    DEPENDS ${API_INFO_OUTPUT_DIR}/imgui_functions.json
            ${API_INFO_OUTPUT_DIR}/imgui_enums.json
            ${API_INFO_OUTPUT_DIR}/imgui_structs.json
            ${API_INFO_OUTPUT_DIR}/imgui_typedefs.json
            ${API_INFO_OUTPUT_DIR}/imgui_typedef_values.json
            ${CMAKE_SOURCE_DIR}/scripts/check_imgui_param_type_coverage.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Checking ImGui API parameter type coverage"
)


# Special target to generate ImGui API info (can be run manually)

add_custom_target(imgui_api_info
    DEPENDS ${API_INFO_OUTPUT_DIR}/imgui_functions.json
            ${API_INFO_OUTPUT_DIR}/imgui_enums.json
            ${API_INFO_OUTPUT_DIR}/imgui_structs.json
            ${API_INFO_OUTPUT_DIR}/imgui_typedefs.json
            ${API_INFO_OUTPUT_DIR}/imgui_typedef_values.json
            ${API_INFO_OUTPUT_DIR}/imgui_param_type_coverage.ok
)

# Make main targets depend on this, so it runs with the build
add_dependencies(ImGui-Designer imgui_api_info)


# Parameter struct and map generation
set(PARAM_GEN_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/generate_imgui_block_params.py")
set(NODE_FACTORY_MAP_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/generate_node_factory_map.py")
set(NODE_PARAMS_MAP_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/generate_node_params_map.py")
set(IMGUI_FUNCTIONS_JSON "${CMAKE_SOURCE_DIR}/scripts/output/imgui_functions.json")
set(GENERATED_PARAMS_DIR "${CMAKE_SOURCE_DIR}/src/generated/params")
set(GENERATED_MAPS_DIR "${CMAKE_SOURCE_DIR}/src/generated/maps")

add_custom_command(
    OUTPUT ${GENERATED_PARAMS_DIR}/ImGuiBlockParams.hpp
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_PARAMS_DIR}
    COMMAND ${Python3_EXECUTABLE} ${PARAM_GEN_SCRIPT}
    DEPENDS ${PARAM_GEN_SCRIPT} ${IMGUI_FUNCTIONS_JSON}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating ImGui parameter structs in build tree"
)

add_custom_command(
    OUTPUT ${GENERATED_MAPS_DIR}/NodeParamsMap.hpp
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_MAPS_DIR}
    COMMAND ${Python3_EXECUTABLE} ${NODE_PARAMS_MAP_SCRIPT}
    DEPENDS ${NODE_PARAMS_MAP_SCRIPT} ${IMGUI_FUNCTIONS_JSON} ${GENERATED_PARAMS_DIR}/ImGuiBlockParams.hpp
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating node_params_map.hpp in build tree"
)

add_custom_command(
    OUTPUT ${MARKER_DIR}/node_factory_map_generated.ok
           ${GENERATED_MAPS_DIR}/NodeFactoryMap.hpp
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_MAPS_DIR}
    COMMAND ${Python3_EXECUTABLE} ${NODE_FACTORY_MAP_SCRIPT}
    COMMAND ${CMAKE_COMMAND} -E touch ${MARKER_DIR}/node_factory_map_generated.ok
    DEPENDS ${NODE_FACTORY_MAP_SCRIPT} ${IMGUI_FUNCTIONS_JSON} ${GENERATED_PARAMS_DIR}/ImGuiBlockParams.hpp
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating node factory map"
)

add_custom_target(imgui_param_structs
    DEPENDS ${GENERATED_PARAMS_DIR}/ImGuiBlockParams.hpp
)

add_custom_target(node_factory_map
    DEPENDS ${MARKER_DIR}/node_factory_map_generated.ok
)

add_custom_target(node_params_map
    DEPENDS ${GENERATED_MAPS_DIR}/NodeParamsMap.hpp
)

add_dependencies(ImGui-Designer imgui_api_info imgui_param_structs node_factory_map node_params_map)

# =============================
# Clean Generated Files Target
# =============================

# Define all generated files that should be cleaned
set(GENERATED_FILES
    # Marker files
    ${MARKER_DIR}/node_factory_map_generated.ok
    ${MARKER_DIR}/param_structs_generated.ok
    ${MARKER_DIR}/node_params_map_generated.ok

    # Generated header files (now in src/generated/)
    ${CMAKE_SOURCE_DIR}/src/generated/params/ImGuiBlockParams.hpp
    ${CMAKE_SOURCE_DIR}/src/generated/maps/NodeFactoryMap.hpp
    ${CMAKE_SOURCE_DIR}/src/generated/maps/NodeParamsMap.hpp
)

# Tell CMake about additional files to clean during "make clean"
# This ensures that generated files are removed along with regular build artifacts
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY
    ADDITIONAL_CLEAN_FILES ${GENERATED_FILES}
)

# Add target to clean all generated files (can be run manually with "make clean_generated")
add_custom_target(clean_generated
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning all generated files..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${GENERATED_FILES}
    COMMAND ${CMAKE_COMMAND} -E echo "All generated files have been removed."
    COMMENT "Removing all auto-generated files from code generation scripts"
)

# Add a target to regenerate all generated files
add_custom_target(regenerate_all
    COMMAND ${CMAKE_COMMAND} -E echo "Regenerating all generated files..."
    DEPENDS clean_generated imgui_api_info imgui_param_structs node_factory_map node_params_map
    COMMENT "Cleaning and regenerating all auto-generated files"
)
