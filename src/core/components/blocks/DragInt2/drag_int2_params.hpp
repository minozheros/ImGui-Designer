#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct DragInt2Params {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<float> v_speed = ParameterBase<float>("v_speed", ParameterType::INPUT);
    ParameterBase<int> v_min = ParameterBase<int>("v_min", ParameterType::INPUT);
    ParameterBase<int> v_max = ParameterBase<int>("v_max", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiSliderFlags> flags = ParameterBase<ImGuiSliderFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    DragInt2Params() {
        params.push_back(&label);
        params.push_back(&v_speed);
        params.push_back(&v_min);
        params.push_back(&v_max);
        params.push_back(&format);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
