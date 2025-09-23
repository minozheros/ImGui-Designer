#pragma once
#include <imgui.h>

struct IsMouseHoveringRectParams {
    const ImVec2& r_min;
    const ImVec2& r_max;
    bool clip;
};
