#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PopStyleVarParams {
    ParameterBase<int> count = ParameterBase<int>("count", ParameterType::INPUT);

    PopStyleVarParams() = default;
};
