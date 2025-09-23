#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetWindowSizeParams {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);
    ParameterBase<const ImVec2&> size = ParameterBase<const ImVec2&>("size", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    SetWindowSizeParams() = default;
};
