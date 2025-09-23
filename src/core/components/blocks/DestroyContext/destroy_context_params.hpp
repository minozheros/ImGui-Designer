#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct DestroyContextParams {
    ParameterBase<ImGuiContext*> ctx = ParameterBase<ImGuiContext*>("ctx", ParameterType::INPUT);

    DestroyContextParams() = default;
};
