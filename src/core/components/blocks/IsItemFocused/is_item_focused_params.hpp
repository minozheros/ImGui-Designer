#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsItemFocusedParams {
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsItemFocusedParams() = default;
};
