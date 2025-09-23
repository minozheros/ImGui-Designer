#pragma once
#include <imgui.h>

struct GetMouseDragDeltaParams {
    ImGuiMouseButton button;
    float lock_threshold;
};
