#pragma once
#include <imgui.h>

struct TableSetBgColorParams {
    ImGuiTableBgTarget target;
    ImU32 color;
    int column_n;
};
