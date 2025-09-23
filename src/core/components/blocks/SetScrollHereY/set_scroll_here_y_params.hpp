#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetScrollHereYParams {
    ParameterBase<float> center_y_ratio = ParameterBase<float>("center_y_ratio", ParameterType::INPUT);

    SetScrollHereYParams() = default;
};
