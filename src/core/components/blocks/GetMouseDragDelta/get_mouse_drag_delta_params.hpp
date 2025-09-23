#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetMouseDragDeltaParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<float> lock_threshold = ParameterBase<float>("lock_threshold", ParameterType::INPUT);
    ParameterBase<ImVec2> return_value = ParameterBase<ImVec2>("return_value", ParameterType::RETURN);

    GetMouseDragDeltaParams() = default;
};
