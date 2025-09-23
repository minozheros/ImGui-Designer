#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ColorConvertRGBtoHSVParams {
    ParameterBase<float> r = ParameterBase<float>("r", ParameterType::INPUT);
    ParameterBase<float> g = ParameterBase<float>("g", ParameterType::INPUT);
    ParameterBase<float> b = ParameterBase<float>("b", ParameterType::INPUT);
    ParameterBase<float&> out_h = ParameterBase<float&>("out_h", ParameterType::INPUT);
    ParameterBase<float&> out_s = ParameterBase<float&>("out_s", ParameterType::INPUT);
    ParameterBase<float&> out_v = ParameterBase<float&>("out_v", ParameterType::INPUT);

    ColorConvertRGBtoHSVParams() = default;
};
