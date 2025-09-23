#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetWindowCollapsedParams {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);
    ParameterBase<bool> collapsed = ParameterBase<bool>("collapsed", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    SetWindowCollapsedParams() = default;
};
