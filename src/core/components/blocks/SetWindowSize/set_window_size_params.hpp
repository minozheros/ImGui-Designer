#pragma once
#include <imgui.h>
#include <string>

struct SetWindowSizeParams {
    std::string name;
    const ImVec2& size;
    ImGuiCond cond;
};
