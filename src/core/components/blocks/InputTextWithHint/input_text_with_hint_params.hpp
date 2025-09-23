#pragma once
#include <imgui.h>
#include <string>

struct InputTextWithHintParams {
    std::string label;
    std::string hint;
    std::string buf;
    size_t buf_size;
    ImGuiInputTextFlags flags;
    ImGuiInputTextCallback callback;
    void* user_data;
};
