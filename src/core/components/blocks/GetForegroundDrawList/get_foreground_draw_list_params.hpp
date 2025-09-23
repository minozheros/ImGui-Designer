#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetForegroundDrawListParams {
    ParameterBase<ImGuiViewport*> viewport = ParameterBase<ImGuiViewport*>("viewport", ParameterType::INPUT);
    ParameterBase<ImDrawList*> return_value = ParameterBase<ImDrawList*>("return_value", ParameterType::RETURN);

    GetForegroundDrawListParams() = default;
};
