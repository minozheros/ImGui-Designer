#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetScrollHereXParams {
    ParameterBase<float> center_x_ratio = ParameterBase<float>("center_x_ratio", ParameterType::INPUT);

    SetScrollHereXParams() = default;
};
