#pragma once
#include <imgui.h>
#include <string>

struct OpenPopupOnItemClickParams {
    std::string str_id;
    ImGuiPopupFlags popup_flags;
};
