#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetMouseClickedCountParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    GetMouseClickedCountParams() = default;
};
