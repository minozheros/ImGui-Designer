#pragma once
#include <imgui.h>
#include <string>

struct RadioButtonParams {
    std::string label;
    int* v;
    int v_button;
};
