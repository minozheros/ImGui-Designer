#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct CheckboxFlagsParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<unsigned int*> flags = ParameterBase<unsigned int*>("flags", ParameterType::INPUT);
    ParameterBase<unsigned int> flags_value = ParameterBase<unsigned int>("flags_value", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    CheckboxFlagsParams() = default;
};
