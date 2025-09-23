#pragma once
#include <imgui.h>
#include <string>

struct CollapsingHeaderParams {
    std::string label;
    bool* p_visible;
    ImGuiTreeNodeFlags flags;
};
