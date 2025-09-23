#pragma once
#include <imgui.h>

struct PushClipRectParams {
    const ImVec2& clip_rect_min;
    const ImVec2& clip_rect_max;
    bool intersect_with_current_clip_rect;
};
