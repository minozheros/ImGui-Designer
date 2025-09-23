#pragma once
#include <imgui.h>

struct BeginMultiSelectParams {
    ImGuiMultiSelectFlags flags;
    int selection_size;
    int items_count;
};
