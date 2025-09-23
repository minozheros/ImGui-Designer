#pragma once
#include <imgui.h>
#include <string>

struct ColorPicker4Params {
    std::string label;
    float col;
    ImGuiColorEditFlags flags;
    const float* ref_col;
};
