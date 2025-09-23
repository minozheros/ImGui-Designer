#pragma once
#include <imgui.h>
#include <string>

struct BeginPopupModalParams {
    std::string name;
    bool* p_open;
    ImGuiWindowFlags flags;
};
