#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SliderAngleParams : public core::IParameterParamsBase {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<float*> v_rad = ParameterBase<float*>("v_rad", ParameterType::INPUT);
    ParameterBase<float> v_degrees_min = ParameterBase<float>("v_degrees_min", ParameterType::INPUT);
    ParameterBase<float> v_degrees_max = ParameterBase<float>("v_degrees_max", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiSliderFlags> flags = ParameterBase<ImGuiSliderFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    SliderAngleParams() {
        params.push_back(&label);
        params.push_back(&v_rad);
        params.push_back(&v_degrees_min);
        params.push_back(&v_degrees_max);
        params.push_back(&format);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
