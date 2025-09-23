#pragma once
#include <imgui.h>
#include <string>

struct SliderScalarNParams {
    std::string label;
    ImGuiDataType data_type;
    void* p_data;
    int components;
    const void* p_min;
    const void* p_max;
    std::string format;
    ImGuiSliderFlags flags;
};
