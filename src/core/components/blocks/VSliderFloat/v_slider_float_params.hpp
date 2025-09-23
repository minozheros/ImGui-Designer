#pragma once
#include <imgui.h>
#include <string>

struct VSliderFloatParams {
    std::string label;
    const ImVec2& size;
    float* v;
    float v_min;
    float v_max;
    std::string format;
    ImGuiSliderFlags flags;
};
