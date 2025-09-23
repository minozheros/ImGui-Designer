#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetColumnWidthParams {
    ParameterBase<int> column_index = ParameterBase<int>("column_index", ParameterType::INPUT);
    ParameterBase<float> width = ParameterBase<float>("width", ParameterType::INPUT);

    SetColumnWidthParams() = default;
};
