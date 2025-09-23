#pragma once
#include <imgui.h>
#include <string>

struct ColorPicker3Params {
    std::string label;
    float col;
    ImGuiColorEditFlags flags;
};
