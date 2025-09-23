#pragma once
#include <imgui.h>
#include <string>

struct DragIntRange2Params {
    std::string label;
    int* v_current_min;
    int* v_current_max;
    float v_speed;
    int v_min;
    int v_max;
    std::string format;
    std::string format_max;
    ImGuiSliderFlags flags;
};
