#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsItemHoveredParams {
    ParameterBase<ImGuiHoveredFlags> flags = ParameterBase<ImGuiHoveredFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsItemHoveredParams() = default;
};
