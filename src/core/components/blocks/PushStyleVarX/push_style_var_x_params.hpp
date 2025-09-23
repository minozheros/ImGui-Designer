#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushStyleVarXParams {
    ParameterBase<ImGuiStyleVar> idx = ParameterBase<ImGuiStyleVar>("idx", ParameterType::INPUT);
    ParameterBase<float> val_x = ParameterBase<float>("val_x", ParameterType::INPUT);

    PushStyleVarXParams() = default;
};
