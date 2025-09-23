#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNavCursorVisibleParams {
    ParameterBase<bool> visible = ParameterBase<bool>("visible", ParameterType::INPUT);

    SetNavCursorVisibleParams() = default;
};
