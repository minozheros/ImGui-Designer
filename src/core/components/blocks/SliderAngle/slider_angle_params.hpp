#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SliderAngleParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<float*> v_rad = ParameterBase<float*>("v_rad", ParameterType::INPUT);
    ParameterBase<float> v_degrees_min = ParameterBase<float>("v_degrees_min", ParameterType::INPUT);
    ParameterBase<float> v_degrees_max = ParameterBase<float>("v_degrees_max", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiSliderFlags> flags = ParameterBase<ImGuiSliderFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    SliderAngleParams() = default;
};
