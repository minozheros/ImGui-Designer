#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetColumnOffsetParams {
    ParameterBase<int> column_index = ParameterBase<int>("column_index", ParameterType::INPUT);
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    GetColumnOffsetParams() = default;
};
