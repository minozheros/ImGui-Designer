#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsMouseDownParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsMouseDownParams() = default;
};
