#pragma once
#include <imgui.h>
#include <string>

struct SetWindowPosParams {
    std::string name;
    const ImVec2& pos;
    ImGuiCond cond;
};
