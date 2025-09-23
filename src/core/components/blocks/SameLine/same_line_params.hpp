#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SameLineParams {
    ParameterBase<float> offset_from_start_x = ParameterBase<float>("offset_from_start_x", ParameterType::INPUT);
    ParameterBase<float> spacing = ParameterBase<float>("spacing", ParameterType::INPUT);

    SameLineParams() = default;
};
