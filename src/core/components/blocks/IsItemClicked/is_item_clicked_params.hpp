#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsItemClickedParams {
    ParameterBase<ImGuiMouseButton> mouse_button = ParameterBase<ImGuiMouseButton>("mouse_button", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsItemClickedParams() = default;
};
