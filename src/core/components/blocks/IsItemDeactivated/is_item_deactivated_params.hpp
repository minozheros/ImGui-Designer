#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsItemDeactivatedParams {
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsItemDeactivatedParams() = default;
};
