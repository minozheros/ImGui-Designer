#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ResetMouseDragDeltaParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);

    ResetMouseDragDeltaParams() = default;
};
