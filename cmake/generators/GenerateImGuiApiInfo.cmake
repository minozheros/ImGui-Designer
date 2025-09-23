# Generate ImGui API Information
find_package(Python3 REQUIRED COMPONENTS Interpreter)


set(IMGUI_H_PATH "${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui.h")
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
add_dependencies(ImGui-Designer_tests imgui_api_info)


# Parameter struct and map generation
set(PARAM_GEN_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/generate_imgui_block_params.py")
set(NODE_FACTORY_MAP_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/generate_node_factory_map.py")
set(NODE_PARAMS_MAP_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/generate_node_params_map.py")
set(IMGUI_FUNCTIONS_JSON "${CMAKE_SOURCE_DIR}/scripts/output/imgui_functions.json")

add_custom_command(
    OUTPUT param_structs_generated.ok
    COMMAND ${Python3_EXECUTABLE} ${PARAM_GEN_SCRIPT}
    COMMAND ${CMAKE_COMMAND} -E touch param_structs_generated.ok
    DEPENDS ${PARAM_GEN_SCRIPT} ${IMGUI_FUNCTIONS_JSON}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating ImGui parameter structs"
)

add_custom_command(
    OUTPUT node_factory_map_generated.ok
    COMMAND ${Python3_EXECUTABLE} ${NODE_FACTORY_MAP_SCRIPT}
    COMMAND ${CMAKE_COMMAND} -E touch node_factory_map_generated.ok
    DEPENDS ${NODE_FACTORY_MAP_SCRIPT} ${IMGUI_FUNCTIONS_JSON}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating node_factory_map.hpp"
)

add_custom_command(
    OUTPUT node_params_map_generated.ok
    COMMAND ${Python3_EXECUTABLE} ${NODE_PARAMS_MAP_SCRIPT}
    COMMAND ${CMAKE_COMMAND} -E touch node_params_map_generated.ok
    DEPENDS ${NODE_PARAMS_MAP_SCRIPT} ${IMGUI_FUNCTIONS_JSON}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating node_params_map.hpp"
)

add_custom_target(imgui_param_structs
    DEPENDS param_structs_generated.ok
)

add_custom_target(node_factory_map
    DEPENDS node_factory_map_generated.ok
)

add_custom_target(node_params_map
    DEPENDS node_params_map_generated.ok
)

add_dependencies(ImGui-Designer imgui_param_structs node_factory_map node_params_map)
add_dependencies(ImGui-Designer_tests imgui_param_structs node_factory_map node_params_map)
