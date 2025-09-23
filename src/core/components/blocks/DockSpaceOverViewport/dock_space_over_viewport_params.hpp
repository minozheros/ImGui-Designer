#pragma once
#include <imgui.h>

struct DockSpaceOverViewportParams {
    ImGuiID dockspace_id;
    const ImGuiViewport* viewport;
    ImGuiDockNodeFlags flags;
    const ImGuiWindowClass* window_class;
};
