#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct InputDoubleParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<double*> v = ParameterBase<double*>("v", ParameterType::INPUT);
    ParameterBase<double> step = ParameterBase<double>("step", ParameterType::INPUT);
    ParameterBase<double> step_fast = ParameterBase<double>("step_fast", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    InputDoubleParams() = default;
};
