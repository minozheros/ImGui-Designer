#pragma once
#include <imgui.h>
#include <string>

struct BeginComboParams {
    std::string label;
    std::string preview_value;
    ImGuiComboFlags flags;
};
