#pragma once
#include <imgui.h>
#include <string>

struct SetWindowCollapsedParams {
    std::string name;
    bool collapsed;
    ImGuiCond cond;
};
