#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct RadioButtonParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<int*> v = ParameterBase<int*>("v", ParameterType::INPUT);
    ParameterBase<int> v_button = ParameterBase<int>("v_button", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    RadioButtonParams() = default;
};
