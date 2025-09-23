#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetWindowPosParams {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);
    ParameterBase<const ImVec2&> pos = ParameterBase<const ImVec2&>("pos", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    SetWindowPosParams() = default;
};
