#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushStyleVarParams {
    ParameterBase<ImGuiStyleVar> idx = ParameterBase<ImGuiStyleVar>("idx", ParameterType::INPUT);
    ParameterBase<const ImVec2&> val = ParameterBase<const ImVec2&>("val", ParameterType::INPUT);

    PushStyleVarParams() = default;
};
