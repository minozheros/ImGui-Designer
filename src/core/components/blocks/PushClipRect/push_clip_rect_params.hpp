#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushClipRectParams {
    ParameterBase<const ImVec2&> clip_rect_min = ParameterBase<const ImVec2&>("clip_rect_min", ParameterType::INPUT);
    ParameterBase<const ImVec2&> clip_rect_max = ParameterBase<const ImVec2&>("clip_rect_max", ParameterType::INPUT);
    ParameterBase<bool> intersect_with_current_clip_rect = ParameterBase<bool>("intersect_with_current_clip_rect", ParameterType::INPUT);

    PushClipRectParams() = default;
};
