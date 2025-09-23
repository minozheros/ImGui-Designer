#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct IsMouseHoveringRectParams {
    ParameterBase<const ImVec2&> r_min = ParameterBase<const ImVec2&>("r_min", ParameterType::INPUT);
    ParameterBase<const ImVec2&> r_max = ParameterBase<const ImVec2&>("r_max", ParameterType::INPUT);
    ParameterBase<bool> clip = ParameterBase<bool>("clip", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    IsMouseHoveringRectParams() {
        params.push_back(&r_min);
        params.push_back(&r_max);
        params.push_back(&clip);
        params.push_back(&return_value);
    }
};
}
