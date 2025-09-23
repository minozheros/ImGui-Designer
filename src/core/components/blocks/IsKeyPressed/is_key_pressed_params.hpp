#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsKeyPressedParams {
    ParameterBase<ImGuiKey> key = ParameterBase<ImGuiKey>("key", ParameterType::INPUT);
    ParameterBase<bool> repeat = ParameterBase<bool>("repeat", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsKeyPressedParams() = default;
};
