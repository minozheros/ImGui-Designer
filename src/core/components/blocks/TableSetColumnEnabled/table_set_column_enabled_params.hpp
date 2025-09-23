#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableSetColumnEnabledParams {
    ParameterBase<int> column_n = ParameterBase<int>("column_n", ParameterType::INPUT);
    ParameterBase<bool> v = ParameterBase<bool>("v", ParameterType::INPUT);

    TableSetColumnEnabledParams() = default;
};
