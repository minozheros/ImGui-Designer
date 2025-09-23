#pragma once
#include <imgui.h>
#include <string>

struct VSliderIntParams {
    std::string label;
    const ImVec2& size;
    int* v;
    int v_min;
    int v_max;
    std::string format;
    ImGuiSliderFlags flags;
};
