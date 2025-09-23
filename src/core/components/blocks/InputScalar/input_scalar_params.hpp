#pragma once
#include <imgui.h>
#include <string>

struct InputScalarParams {
    std::string label;
    ImGuiDataType data_type;
    void* p_data;
    const void* p_step;
    const void* p_step_fast;
    std::string format;
    ImGuiInputTextFlags flags;
};
