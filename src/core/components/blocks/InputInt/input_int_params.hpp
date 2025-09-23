#pragma once
#include <imgui.h>
#include <string>

struct InputIntParams {
    std::string label;
    int* v;
    int step;
    int step_fast;
    ImGuiInputTextFlags flags;
};
