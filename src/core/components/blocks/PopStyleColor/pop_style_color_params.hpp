#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PopStyleColorParams {
    ParameterBase<int> count = ParameterBase<int>("count", ParameterType::INPUT);

    PopStyleColorParams() = default;
};
