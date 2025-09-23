#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushIDParams {
    ParameterBase<int> int_id = ParameterBase<int>("int_id", ParameterType::INPUT);

    PushIDParams() = default;
};
