#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetCursorPosYParams {
    ParameterBase<float> local_y = ParameterBase<float>("local_y", ParameterType::INPUT);

    SetCursorPosYParams() = default;
};
