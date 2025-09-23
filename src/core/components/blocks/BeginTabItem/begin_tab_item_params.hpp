#pragma once
#include <imgui.h>
#include <string>

struct BeginTabItemParams {
    std::string label;
    bool* p_open;
    ImGuiTabItemFlags flags;
};
