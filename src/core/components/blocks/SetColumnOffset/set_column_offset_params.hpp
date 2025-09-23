#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetColumnOffsetParams {
    ParameterBase<int> column_index = ParameterBase<int>("column_index", ParameterType::INPUT);
    ParameterBase<float> offset_x = ParameterBase<float>("offset_x", ParameterType::INPUT);

    SetColumnOffsetParams() = default;
};
