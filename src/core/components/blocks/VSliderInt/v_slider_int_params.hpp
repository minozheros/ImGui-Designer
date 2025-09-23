#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct VSliderIntParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const ImVec2&> size = ParameterBase<const ImVec2&>("size", ParameterType::INPUT);
    ParameterBase<int*> v = ParameterBase<int*>("v", ParameterType::INPUT);
    ParameterBase<int> v_min = ParameterBase<int>("v_min", ParameterType::INPUT);
    ParameterBase<int> v_max = ParameterBase<int>("v_max", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiSliderFlags> flags = ParameterBase<ImGuiSliderFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    VSliderIntParams() = default;
};
