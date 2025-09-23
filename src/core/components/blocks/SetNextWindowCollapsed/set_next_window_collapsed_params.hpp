#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextWindowCollapsedParams {
    ParameterBase<bool> collapsed = ParameterBase<bool>("collapsed", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    SetNextWindowCollapsedParams() = default;
};
