#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetCursorPosXParams {
    ParameterBase<float> local_x = ParameterBase<float>("local_x", ParameterType::INPUT);

    SetCursorPosXParams() = default;
};
