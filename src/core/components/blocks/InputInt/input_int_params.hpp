#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct InputIntParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<int*> v = ParameterBase<int*>("v", ParameterType::INPUT);
    ParameterBase<int> step = ParameterBase<int>("step", ParameterType::INPUT);
    ParameterBase<int> step_fast = ParameterBase<int>("step_fast", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    InputIntParams() {
        params.push_back(&label);
        params.push_back(&v);
        params.push_back(&step);
        params.push_back(&step_fast);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
