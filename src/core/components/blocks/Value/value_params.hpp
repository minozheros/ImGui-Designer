#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ValueParams {
    ParameterBase<const char*> prefix = ParameterBase<const char*>("prefix", ParameterType::INPUT);
    ParameterBase<float> v = ParameterBase<float>("v", ParameterType::INPUT);
    ParameterBase<const char*> float_format = ParameterBase<const char*>("float_format", ParameterType::INPUT);

    ValueParams() = default;
};
