#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct InputIntParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<int*> v = ParameterBase<int*>("v", ParameterType::INPUT);
    ParameterBase<int> step = ParameterBase<int>("step", ParameterType::INPUT);
    ParameterBase<int> step_fast = ParameterBase<int>("step_fast", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    InputIntParams() = default;
};
