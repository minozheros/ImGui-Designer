#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetScrollFromPosYParams {
    ParameterBase<float> local_y = ParameterBase<float>("local_y", ParameterType::INPUT);
    ParameterBase<float> center_y_ratio = ParameterBase<float>("center_y_ratio", ParameterType::INPUT);

    SetScrollFromPosYParams() = default;
};
