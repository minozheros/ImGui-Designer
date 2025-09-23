#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextWindowViewportParams {
    ParameterBase<ImGuiID> viewport_id = ParameterBase<ImGuiID>("viewport_id", ParameterType::INPUT);

    SetNextWindowViewportParams() = default;
};
