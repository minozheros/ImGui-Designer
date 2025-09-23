#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct DebugFlashStyleColorParams {
    ParameterBase<ImGuiCol> idx = ParameterBase<ImGuiCol>("idx", ParameterType::INPUT);

    DebugFlashStyleColorParams() = default;
};
