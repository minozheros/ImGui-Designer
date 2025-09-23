#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsKeyReleasedParams {
    ParameterBase<ImGuiKey> key = ParameterBase<ImGuiKey>("key", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsKeyReleasedParams() = default;
};
