#pragma once
#include <imgui.h>
#include <string>

struct InputInt3Params {
    std::string label;
    int v;
    ImGuiInputTextFlags flags;
};
