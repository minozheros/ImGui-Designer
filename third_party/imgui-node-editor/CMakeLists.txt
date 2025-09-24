

include(FetchContent)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor.cpp")
    FetchContent_Declare(
        imguinodeeditor
        GIT_REPOSITORY https://github.com/thedmd/imgui-node-editor.git
        GIT_TAG master
        PATCH_COMMAND bash -c "sed -i 's/ImGui::GetKeyIndex(ImGuiKey_X)/ImGuiKey_X/g' imgui_node_editor.cpp && sed -i 's/ImGui::GetKeyIndex(ImGuiKey_C)/ImGuiKey_C/g' imgui_node_editor.cpp && sed -i 's/ImGui::GetKeyIndex(ImGuiKey_V)/ImGuiKey_V/g' imgui_node_editor.cpp && sed -i 's/ImGui::GetKeyIndex(ImGuiKey_D)/ImGuiKey_D/g' imgui_node_editor.cpp && sed -i 's/ImGui::GetKeyIndex(ImGuiKey_Space)/ImGuiKey_Space/g' imgui_node_editor.cpp && sed -i 's/ImGui::GetKeyIndex(ImGuiKey_Delete)/ImGuiKey_Delete/g' imgui_node_editor.cpp"
    )
    FetchContent_MakeAvailable(imguinodeeditor)
    set(IMGUI_NODE_EDITOR_SRC_DIR ${imguinodeeditor_SOURCE_DIR})
else()
    set(IMGUI_NODE_EDITOR_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()


file(GLOB IMGUI_NODE_EDITOR_SOURCES ${IMGUI_NODE_EDITOR_SRC_DIR}/*.cpp)
add_library(imguinodeeditor STATIC ${IMGUI_NODE_EDITOR_SOURCES})
target_include_directories(imguinodeeditor PUBLIC ${IMGUI_NODE_EDITOR_SRC_DIR})
target_link_libraries(imguinodeeditor PUBLIC imgui)
