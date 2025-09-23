#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct InputFloatParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<float*> v = ParameterBase<float*>("v", ParameterType::INPUT);
    ParameterBase<float> step = ParameterBase<float>("step", ParameterType::INPUT);
    ParameterBase<float> step_fast = ParameterBase<float>("step_fast", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    InputFloatParams() {
        params.push_back(&label);
        params.push_back(&v);
        params.push_back(&step);
        params.push_back(&step_fast);
        params.push_back(&format);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
