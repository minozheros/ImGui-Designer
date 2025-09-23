#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetWindowWidthParams {
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetWindowWidthParams() {
        params.push_back(&return_value);
    }
};
}
