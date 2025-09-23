#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushStyleVarYParams {
    ParameterBase<ImGuiStyleVar> idx = ParameterBase<ImGuiStyleVar>("idx", ParameterType::INPUT);
    ParameterBase<float> val_y = ParameterBase<float>("val_y", ParameterType::INPUT);

    PushStyleVarYParams() = default;
};
