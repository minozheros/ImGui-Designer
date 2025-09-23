#pragma once
#include <imgui.h>
#include <string>

struct DragInt2Params {
    std::string label;
    int v;
    float v_speed;
    int v_min;
    int v_max;
    std::string format;
    ImGuiSliderFlags flags;
};
