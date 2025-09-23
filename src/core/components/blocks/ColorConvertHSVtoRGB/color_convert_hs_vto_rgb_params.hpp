#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ColorConvertHSVtoRGBParams {
    ParameterBase<float> h = ParameterBase<float>("h", ParameterType::INPUT);
    ParameterBase<float> s = ParameterBase<float>("s", ParameterType::INPUT);
    ParameterBase<float> v = ParameterBase<float>("v", ParameterType::INPUT);
    ParameterBase<float&> out_r = ParameterBase<float&>("out_r", ParameterType::INPUT);
    ParameterBase<float&> out_g = ParameterBase<float&>("out_g", ParameterType::INPUT);
    ParameterBase<float&> out_b = ParameterBase<float&>("out_b", ParameterType::INPUT);

    ColorConvertHSVtoRGBParams() = default;
};
