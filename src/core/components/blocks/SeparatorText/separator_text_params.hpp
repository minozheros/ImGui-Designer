#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SeparatorTextParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);

    SeparatorTextParams() = default;
};
