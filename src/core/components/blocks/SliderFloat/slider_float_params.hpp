#pragma once
#include <imgui.h>
#include <string>

struct SliderFloatParams {
    std::string label;
    float* v;
    float v_min;
    float v_max;
    std::string format;
    ImGuiSliderFlags flags;
};
