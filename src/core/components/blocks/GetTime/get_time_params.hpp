#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetTimeParams {
    ParameterBase<double> return_value = ParameterBase<double>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetTimeParams() {
        params.push_back(&return_value);
    }
};
}
