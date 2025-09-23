#pragma once
#include <imgui.h>
#include <string>

struct SliderScalarParams {
    std::string label;
    ImGuiDataType data_type;
    void* p_data;
    const void* p_min;
    const void* p_max;
    std::string format;
    ImGuiSliderFlags flags;
};
