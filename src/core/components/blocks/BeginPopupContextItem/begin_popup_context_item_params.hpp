#pragma once
#include <imgui.h>
#include <string>

struct BeginPopupContextItemParams {
    std::string str_id;
    ImGuiPopupFlags popup_flags;
};
