#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextWindowClassParams {
    ParameterBase<const ImGuiWindowClass*> window_class = ParameterBase<const ImGuiWindowClass*>("window_class", ParameterType::INPUT);

    SetNextWindowClassParams() = default;
};
