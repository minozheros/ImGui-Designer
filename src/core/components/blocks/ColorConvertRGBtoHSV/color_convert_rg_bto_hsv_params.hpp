#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct ColorConvertRGBtoHSVParams : public core::IParameterParamsBase {
    ParameterBase<float> r = ParameterBase<float>("r", ParameterType::INPUT);
    ParameterBase<float> g = ParameterBase<float>("g", ParameterType::INPUT);
    ParameterBase<float> b = ParameterBase<float>("b", ParameterType::INPUT);
    ParameterBase<float&> out_h = ParameterBase<float&>("out_h", ParameterType::INPUT);
    ParameterBase<float&> out_s = ParameterBase<float&>("out_s", ParameterType::INPUT);
    ParameterBase<float&> out_v = ParameterBase<float&>("out_v", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    ColorConvertRGBtoHSVParams() {
        params.push_back(&r);
        params.push_back(&g);
        params.push_back(&b);
        params.push_back(&out_h);
        params.push_back(&out_s);
        params.push_back(&out_v);
    }
};
}
