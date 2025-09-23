#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextWindowDockIDParams {
    ParameterBase<ImGuiID> dock_id = ParameterBase<ImGuiID>("dock_id", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    SetNextWindowDockIDParams() = default;
};
