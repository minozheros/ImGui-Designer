

include(FetchContent)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor.cpp")
    FetchContent_Declare(
        imgui-node-editor
        GIT_REPOSITORY https://github.com/thedmd/imgui-node-editor.git
        GIT_TAG e78e447900909a051817a760efe13fe83e6e1afc
    )
    FetchContent_MakeAvailable(imgui-node-editor)
    set(IMGUI_NODE_EDITOR_SRC_DIR ${imgui-node-editor_SOURCE_DIR})
else()
    set(IMGUI_NODE_EDITOR_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()


file(GLOB IMGUI_NODE_EDITOR_SOURCES ${IMGUI_NODE_EDITOR_SRC_DIR}/*.cpp)
add_library(imgui-node-editor STATIC ${IMGUI_NODE_EDITOR_SOURCES})
target_include_directories(imgui-node-editor PUBLIC ${IMGUI_NODE_EDITOR_SRC_DIR})
target_link_libraries(imgui-node-editor PUBLIC imgui)
