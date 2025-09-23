#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct IsMousePosValidParams {
    ParameterBase<const ImVec2*> mouse_pos = ParameterBase<const ImVec2*>("mouse_pos", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    IsMousePosValidParams() {
        params.push_back(&mouse_pos);
        params.push_back(&return_value);
    }
};
}
