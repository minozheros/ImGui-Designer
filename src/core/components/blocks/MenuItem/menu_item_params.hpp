#pragma once
#include <imgui.h>
#include <string>

struct MenuItemParams {
    std::string label;
    std::string shortcut;
    bool* p_selected;
    bool enabled;
};
