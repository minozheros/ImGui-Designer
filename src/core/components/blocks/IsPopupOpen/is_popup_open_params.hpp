#pragma once
#include <imgui.h>
#include <string>

struct IsPopupOpenParams {
    std::string str_id;
    ImGuiPopupFlags flags;
};
