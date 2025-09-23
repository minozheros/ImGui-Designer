#pragma once
#include <imgui.h>

struct SetNextWindowSizeParams {
    const ImVec2& size;
    ImGuiCond cond;
};
