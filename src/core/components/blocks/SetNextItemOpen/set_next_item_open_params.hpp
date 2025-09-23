#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextItemOpenParams {
    ParameterBase<bool> is_open = ParameterBase<bool>("is_open", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    SetNextItemOpenParams() = default;
};
