#pragma once
#include <imgui.h>
#include <string>

struct DragFloatParams {
    std::string label;
    float* v;
    float v_speed;
    float v_min;
    float v_max;
    std::string format;
    ImGuiSliderFlags flags;
};
