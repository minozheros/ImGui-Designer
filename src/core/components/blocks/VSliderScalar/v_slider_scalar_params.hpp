#pragma once
#include <imgui.h>
#include <string>

struct VSliderScalarParams {
    std::string label;
    const ImVec2& size;
    ImGuiDataType data_type;
    void* p_data;
    const void* p_min;
    const void* p_max;
    std::string format;
    ImGuiSliderFlags flags;
};
