#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct BeginMenuParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<bool> enabled = ParameterBase<bool>("enabled", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    BeginMenuParams() = default;
};
