#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SliderFloat3Params {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<float> v_min = ParameterBase<float>("v_min", ParameterType::INPUT);
    ParameterBase<float> v_max = ParameterBase<float>("v_max", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiSliderFlags> flags = ParameterBase<ImGuiSliderFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    SliderFloat3Params() {
        params.push_back(&label);
        params.push_back(&v_min);
        params.push_back(&v_max);
        params.push_back(&format);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
