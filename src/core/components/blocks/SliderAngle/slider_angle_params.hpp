#pragma once
#include <imgui.h>
#include <string>

struct SliderAngleParams {
    std::string label;
    float* v_rad;
    float v_degrees_min;
    float v_degrees_max;
    std::string format;
    ImGuiSliderFlags flags;
};
