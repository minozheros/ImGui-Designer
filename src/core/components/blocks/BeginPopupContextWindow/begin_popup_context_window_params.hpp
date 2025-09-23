#pragma once
#include <imgui.h>
#include <string>

struct BeginPopupContextWindowParams {
    std::string str_id;
    ImGuiPopupFlags popup_flags;
};
