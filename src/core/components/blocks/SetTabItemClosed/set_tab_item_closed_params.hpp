#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetTabItemClosedParams {
    ParameterBase<const char*> tab_or_docked_window_label = ParameterBase<const char*>("tab_or_docked_window_label", ParameterType::INPUT);

    SetTabItemClosedParams() = default;
};
