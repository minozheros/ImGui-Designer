#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetCurrentContextParams {
    ParameterBase<ImGuiContext*> return_value = ParameterBase<ImGuiContext*>("return_value", ParameterType::RETURN);

    GetCurrentContextParams() = default;
};
