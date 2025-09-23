#pragma once
#include <imgui.h>
#include <string>

struct InputInt2Params {
    std::string label;
    int v;
    ImGuiInputTextFlags flags;
};
