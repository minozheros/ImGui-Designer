#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct DragScalarNParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiDataType> data_type = ParameterBase<ImGuiDataType>("data_type", ParameterType::INPUT);
    ParameterBase<void*> p_data = ParameterBase<void*>("p_data", ParameterType::OUTPUT);
    ParameterBase<int> components = ParameterBase<int>("components", ParameterType::INPUT);
    ParameterBase<float> v_speed = ParameterBase<float>("v_speed", ParameterType::INPUT);
    ParameterBase<const void*> p_min = ParameterBase<const void*>("p_min", ParameterType::OUTPUT);
    ParameterBase<const void*> p_max = ParameterBase<const void*>("p_max", ParameterType::OUTPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiSliderFlags> flags = ParameterBase<ImGuiSliderFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    DragScalarNParams() = default;
};
