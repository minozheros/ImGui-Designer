#pragma once
#include <imgui.h>
#include <string>

struct InvisibleButtonParams {
    std::string str_id;
    const ImVec2& size;
    ImGuiButtonFlags flags;
};
