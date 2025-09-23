#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct CalcItemWidthParams {
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    CalcItemWidthParams() = default;
};
