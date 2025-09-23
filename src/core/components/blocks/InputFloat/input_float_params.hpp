#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct InputFloatParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<float*> v = ParameterBase<float*>("v", ParameterType::INPUT);
    ParameterBase<float> step = ParameterBase<float>("step", ParameterType::INPUT);
    ParameterBase<float> step_fast = ParameterBase<float>("step_fast", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    InputFloatParams() = default;
};
