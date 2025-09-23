#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct DragFloatRange2Params {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<float*> v_current_min = ParameterBase<float*>("v_current_min", ParameterType::INPUT);
    ParameterBase<float*> v_current_max = ParameterBase<float*>("v_current_max", ParameterType::INPUT);
    ParameterBase<float> v_speed = ParameterBase<float>("v_speed", ParameterType::INPUT);
    ParameterBase<float> v_min = ParameterBase<float>("v_min", ParameterType::INPUT);
    ParameterBase<float> v_max = ParameterBase<float>("v_max", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<const char*> format_max = ParameterBase<const char*>("format_max", ParameterType::INPUT);
    ParameterBase<ImGuiSliderFlags> flags = ParameterBase<ImGuiSliderFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    DragFloatRange2Params() = default;
};
