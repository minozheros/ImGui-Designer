#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ValueParams {
    ParameterBase<const char*> prefix = ParameterBase<const char*>("prefix", ParameterType::INPUT);
    ParameterBase<float> v = ParameterBase<float>("v", ParameterType::INPUT);
    ParameterBase<const char*> float_format = ParameterBase<const char*>("float_format", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    ValueParams() {
        params.push_back(&prefix);
        params.push_back(&v);
        params.push_back(&float_format);
    }
};
}
