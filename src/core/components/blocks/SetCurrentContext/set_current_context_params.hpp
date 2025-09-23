#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetCurrentContextParams {
    ParameterBase<ImGuiContext*> ctx = ParameterBase<ImGuiContext*>("ctx", ParameterType::INPUT);

    SetCurrentContextParams() = default;
};
