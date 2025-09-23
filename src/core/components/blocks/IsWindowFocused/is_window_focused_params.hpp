#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsWindowFocusedParams {
    ParameterBase<ImGuiFocusedFlags> flags = ParameterBase<ImGuiFocusedFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsWindowFocusedParams() = default;
};
