#pragma once
#include <imgui.h>
#include <string>

struct InputInt4Params {
    std::string label;
    int v;
    ImGuiInputTextFlags flags;
};
