#pragma once
#include <imgui.h>
#include <string>

struct InputFloat4Params {
    std::string label;
    float v;
    std::string format;
    ImGuiInputTextFlags flags;
};
