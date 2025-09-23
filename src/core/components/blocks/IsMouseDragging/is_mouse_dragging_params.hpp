#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsMouseDraggingParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<float> lock_threshold = ParameterBase<float>("lock_threshold", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsMouseDraggingParams() = default;
};
