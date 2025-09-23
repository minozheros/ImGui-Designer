#pragma once
#include <imgui.h>
#include <string>

struct InputDoubleParams {
    std::string label;
    double* v;
    double step;
    double step_fast;
    std::string format;
    ImGuiInputTextFlags flags;
};
