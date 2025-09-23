#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushStyleColorParams {
    ParameterBase<ImGuiCol> idx = ParameterBase<ImGuiCol>("idx", ParameterType::INPUT);
    ParameterBase<const ImVec4&> col = ParameterBase<const ImVec4&>("col", ParameterType::INPUT);

    PushStyleColorParams() = default;
};
