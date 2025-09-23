#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ColumnsParams {
    ParameterBase<int> count = ParameterBase<int>("count", ParameterType::INPUT);
    ParameterBase<const char*> id = ParameterBase<const char*>("id", ParameterType::INPUT);
    ParameterBase<bool> borders = ParameterBase<bool>("borders", ParameterType::INPUT);

    ColumnsParams() = default;
};
