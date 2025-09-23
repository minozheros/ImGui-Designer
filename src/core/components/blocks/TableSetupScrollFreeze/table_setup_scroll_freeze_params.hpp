#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableSetupScrollFreezeParams {
    ParameterBase<int> cols = ParameterBase<int>("cols", ParameterType::INPUT);
    ParameterBase<int> rows = ParameterBase<int>("rows", ParameterType::INPUT);

    TableSetupScrollFreezeParams() = default;
};
