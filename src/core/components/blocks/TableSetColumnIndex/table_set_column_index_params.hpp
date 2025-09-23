#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableSetColumnIndexParams {
    ParameterBase<int> column_n = ParameterBase<int>("column_n", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    TableSetColumnIndexParams() = default;
};
