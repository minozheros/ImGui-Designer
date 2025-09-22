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
