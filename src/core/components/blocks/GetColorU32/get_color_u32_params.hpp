#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetColorU32Params {
    ParameterBase<ImU32> col = ParameterBase<ImU32>("col", ParameterType::INPUT);
    ParameterBase<float> alpha_mul = ParameterBase<float>("alpha_mul", ParameterType::INPUT);
    ParameterBase<ImU32> return_value = ParameterBase<ImU32>("return_value", ParameterType::RETURN);

    GetColorU32Params() = default;
};
