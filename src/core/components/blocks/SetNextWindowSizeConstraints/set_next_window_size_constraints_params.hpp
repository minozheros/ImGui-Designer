#pragma once
#include <imgui.h>

struct SetNextWindowSizeConstraintsParams {
    const ImVec2& size_min;
    const ImVec2& size_max;
    ImGuiSizeCallback custom_callback;
    void* custom_callback_data;
};
