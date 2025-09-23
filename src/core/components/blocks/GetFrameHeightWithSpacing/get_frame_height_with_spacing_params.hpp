#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetFrameHeightWithSpacingParams {
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    GetFrameHeightWithSpacingParams() = default;
};
