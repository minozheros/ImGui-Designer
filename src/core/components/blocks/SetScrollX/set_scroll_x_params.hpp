#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetScrollXParams {
    ParameterBase<float> scroll_x = ParameterBase<float>("scroll_x", ParameterType::INPUT);

    SetScrollXParams() = default;
};
