#pragma once
#include <imgui.h>
#include <string>

struct SliderInt3Params {
    std::string label;
    int v;
    int v_min;
    int v_max;
    std::string format;
    ImGuiSliderFlags flags;
};
