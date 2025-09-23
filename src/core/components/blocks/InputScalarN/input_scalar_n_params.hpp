#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

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

    InputScalarNParams() = default;
};
