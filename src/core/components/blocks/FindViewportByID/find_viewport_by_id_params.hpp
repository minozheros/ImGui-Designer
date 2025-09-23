#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct FindViewportByIDParams {
    ParameterBase<ImGuiID> id = ParameterBase<ImGuiID>("id", ParameterType::INPUT);
    ParameterBase<ImGuiViewport*> return_value = ParameterBase<ImGuiViewport*>("return_value", ParameterType::RETURN);

    FindViewportByIDParams() = default;
};
