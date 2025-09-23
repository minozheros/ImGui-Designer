#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetKeyPressedAmountParams {
    ParameterBase<ImGuiKey> key = ParameterBase<ImGuiKey>("key", ParameterType::INPUT);
    ParameterBase<float> repeat_delay = ParameterBase<float>("repeat_delay", ParameterType::INPUT);
    ParameterBase<float> rate = ParameterBase<float>("rate", ParameterType::INPUT);
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    GetKeyPressedAmountParams() = default;
};
