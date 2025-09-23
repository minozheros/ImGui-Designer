#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsAnyItemActiveParams {
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsAnyItemActiveParams() = default;
};
