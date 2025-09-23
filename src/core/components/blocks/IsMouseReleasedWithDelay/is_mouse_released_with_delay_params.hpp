#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsMouseReleasedWithDelayParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<float> delay = ParameterBase<float>("delay", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsMouseReleasedWithDelayParams() = default;
};
