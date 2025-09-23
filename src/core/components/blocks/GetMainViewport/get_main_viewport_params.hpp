#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetMainViewportParams {
    ParameterBase<ImGuiViewport*> return_value = ParameterBase<ImGuiViewport*>("return_value", ParameterType::RETURN);

    GetMainViewportParams() = default;
};
