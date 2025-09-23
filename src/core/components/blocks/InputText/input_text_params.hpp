#pragma once
#include <imgui.h>
#include <string>

struct InputTextParams {
    std::string label;
    std::string buf;
    size_t buf_size;
    ImGuiInputTextFlags flags;
    ImGuiInputTextCallback callback;
    void* user_data;
};
