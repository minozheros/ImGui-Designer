#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetScrollYParams {
    ParameterBase<float> scroll_y = ParameterBase<float>("scroll_y", ParameterType::INPUT);

    SetScrollYParams() = default;
};
