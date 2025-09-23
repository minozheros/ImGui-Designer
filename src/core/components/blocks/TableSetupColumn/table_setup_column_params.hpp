#pragma once
#include <imgui.h>
#include <string>

struct TableSetupColumnParams {
    std::string label;
    ImGuiTableColumnFlags flags;
    float init_width_or_weight;
    ImGuiID user_id;
};
