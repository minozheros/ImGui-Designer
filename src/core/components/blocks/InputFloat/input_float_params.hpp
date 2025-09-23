#pragma once
#include <imgui.h>
#include <string>

struct InputFloatParams {
    std::string label;
    float* v;
    float step;
    float step_fast;
    std::string format;
    ImGuiInputTextFlags flags;
};
