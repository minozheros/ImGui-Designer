#pragma once
#include <imgui.h>
#include <string>

struct ColorEdit3Params {
    std::string label;
    float col;
    ImGuiColorEditFlags flags;
};
