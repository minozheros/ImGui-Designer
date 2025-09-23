#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushTextWrapPosParams {
    ParameterBase<float> wrap_local_pos_x = ParameterBase<float>("wrap_local_pos_x", ParameterType::INPUT);

    PushTextWrapPosParams() = default;
};
