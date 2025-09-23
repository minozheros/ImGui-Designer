#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsRectVisibleParams {
    ParameterBase<const ImVec2&> rect_min = ParameterBase<const ImVec2&>("rect_min", ParameterType::INPUT);
    ParameterBase<const ImVec2&> rect_max = ParameterBase<const ImVec2&>("rect_max", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsRectVisibleParams() = default;
};
