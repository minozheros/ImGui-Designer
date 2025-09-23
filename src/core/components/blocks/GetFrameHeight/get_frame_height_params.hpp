#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetFrameHeightParams {
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    GetFrameHeightParams() = default;
};
