#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsItemActiveParams {
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsItemActiveParams() = default;
};
