#pragma once
#include <imgui.h>
#include <string>

struct SetDragDropPayloadParams {
    std::string type;
    const void* data;
    size_t sz;
    ImGuiCond cond;
};
