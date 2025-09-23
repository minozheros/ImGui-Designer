#pragma once
#include <imgui.h>
#include <string>

struct DragFloatRange2Params {
    std::string label;
    float* v_current_min;
    float* v_current_max;
    float v_speed;
    float v_min;
    float v_max;
    std::string format;
    std::string format_max;
    ImGuiSliderFlags flags;
};
