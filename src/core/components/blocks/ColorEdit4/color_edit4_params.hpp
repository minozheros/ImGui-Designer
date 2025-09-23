#pragma once
#include <imgui.h>
#include <string>

struct ColorEdit4Params {
    std::string label;
    float col;
    ImGuiColorEditFlags flags;
};
