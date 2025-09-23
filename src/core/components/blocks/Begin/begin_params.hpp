#pragma once
#include <imgui.h>
#include <string>

struct BeginParams {
    std::string name;
    bool* p_open;
    ImGuiWindowFlags flags;
};
