#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsMouseHoveringRectParams {
    ParameterBase<const ImVec2&> r_min = ParameterBase<const ImVec2&>("r_min", ParameterType::INPUT);
    ParameterBase<const ImVec2&> r_max = ParameterBase<const ImVec2&>("r_max", ParameterType::INPUT);
    ParameterBase<bool> clip = ParameterBase<bool>("clip", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsMouseHoveringRectParams() = default;
};
