#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetColumnWidthParams {
    ParameterBase<int> column_index = ParameterBase<int>("column_index", ParameterType::INPUT);
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    GetColumnWidthParams() = default;
};
