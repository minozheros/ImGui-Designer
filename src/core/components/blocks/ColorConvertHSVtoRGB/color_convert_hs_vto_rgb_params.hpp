#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct ColorConvertHSVtoRGBParams : public core::IParameterParamsBase {
    ParameterBase<float> h = ParameterBase<float>("h", ParameterType::INPUT);
    ParameterBase<float> s = ParameterBase<float>("s", ParameterType::INPUT);
    ParameterBase<float> v = ParameterBase<float>("v", ParameterType::INPUT);
    ParameterBase<float&> out_r = ParameterBase<float&>("out_r", ParameterType::INPUT);
    ParameterBase<float&> out_g = ParameterBase<float&>("out_g", ParameterType::INPUT);
    ParameterBase<float&> out_b = ParameterBase<float&>("out_b", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    ColorConvertHSVtoRGBParams() {
        params.push_back(&h);
        params.push_back(&s);
        params.push_back(&v);
        params.push_back(&out_r);
        params.push_back(&out_g);
        params.push_back(&out_b);
    }
};
}
