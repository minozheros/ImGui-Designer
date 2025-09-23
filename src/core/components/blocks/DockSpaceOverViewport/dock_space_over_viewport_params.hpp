#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct DockSpaceOverViewportParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiID> dockspace_id = ParameterBase<ImGuiID>("dockspace_id", ParameterType::INPUT);
    ParameterBase<const ImGuiViewport*> viewport = ParameterBase<const ImGuiViewport*>("viewport", ParameterType::INPUT);
    ParameterBase<ImGuiDockNodeFlags> flags = ParameterBase<ImGuiDockNodeFlags>("flags", ParameterType::INPUT);
    ParameterBase<const ImGuiWindowClass*> window_class = ParameterBase<const ImGuiWindowClass*>("window_class", ParameterType::INPUT);
    ParameterBase<ImGuiID> return_value = ParameterBase<ImGuiID>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    DockSpaceOverViewportParams() {
        params.push_back(&dockspace_id);
        params.push_back(&viewport);
        params.push_back(&flags);
        params.push_back(&window_class);
        params.push_back(&return_value);
    }
};
}
