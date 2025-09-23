#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetTimeParams {
    ParameterBase<double> return_value = ParameterBase<double>("return_value", ParameterType::RETURN);

    GetTimeParams() = default;
};
