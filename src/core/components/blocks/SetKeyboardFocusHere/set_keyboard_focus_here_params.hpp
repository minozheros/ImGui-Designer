#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetKeyboardFocusHereParams {
    ParameterBase<int> offset = ParameterBase<int>("offset", ParameterType::INPUT);

    SetKeyboardFocusHereParams() = default;
};
