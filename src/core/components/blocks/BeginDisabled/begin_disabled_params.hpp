#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct BeginDisabledParams {
    ParameterBase<bool> disabled = ParameterBase<bool>("disabled", ParameterType::INPUT);

    BeginDisabledParams() = default;
};
