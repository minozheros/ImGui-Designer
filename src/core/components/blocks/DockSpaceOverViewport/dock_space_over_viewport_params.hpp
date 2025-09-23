#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct DockSpaceOverViewportParams {
    ParameterBase<ImGuiID> dockspace_id = ParameterBase<ImGuiID>("dockspace_id", ParameterType::INPUT);
    ParameterBase<const ImGuiViewport*> viewport = ParameterBase<const ImGuiViewport*>("viewport", ParameterType::INPUT);
    ParameterBase<ImGuiDockNodeFlags> flags = ParameterBase<ImGuiDockNodeFlags>("flags", ParameterType::INPUT);
    ParameterBase<const ImGuiWindowClass*> window_class = ParameterBase<const ImGuiWindowClass*>("window_class", ParameterType::INPUT);
    ParameterBase<ImGuiID> return_value = ParameterBase<ImGuiID>("return_value", ParameterType::RETURN);

    DockSpaceOverViewportParams() = default;
};
