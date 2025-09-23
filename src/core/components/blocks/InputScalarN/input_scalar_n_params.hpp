#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct InputScalarNParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiDataType> data_type = ParameterBase<ImGuiDataType>("data_type", ParameterType::INPUT);
    ParameterBase<void*> p_data = ParameterBase<void*>("p_data", ParameterType::OUTPUT);
    ParameterBase<int> components = ParameterBase<int>("components", ParameterType::INPUT);
    ParameterBase<const void*> p_step = ParameterBase<const void*>("p_step", ParameterType::OUTPUT);
    ParameterBase<const void*> p_step_fast = ParameterBase<const void*>("p_step_fast", ParameterType::OUTPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    InputScalarNParams() {
        params.push_back(&label);
        params.push_back(&data_type);
        params.push_back(&p_data);
        params.push_back(&components);
        params.push_back(&p_step);
        params.push_back(&p_step_fast);
        params.push_back(&format);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
