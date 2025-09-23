#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetScrollFromPosXParams {
    ParameterBase<float> local_x = ParameterBase<float>("local_x", ParameterType::INPUT);
    ParameterBase<float> center_x_ratio = ParameterBase<float>("center_x_ratio", ParameterType::INPUT);

    SetScrollFromPosXParams() = default;
};
