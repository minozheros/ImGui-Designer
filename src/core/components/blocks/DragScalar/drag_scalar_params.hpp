#pragma once
#include <imgui.h>
#include <string>

struct DragScalarParams {
    std::string label;
    ImGuiDataType data_type;
    void* p_data;
    float v_speed;
    const void* p_min;
    const void* p_max;
    std::string format;
    ImGuiSliderFlags flags;
};
