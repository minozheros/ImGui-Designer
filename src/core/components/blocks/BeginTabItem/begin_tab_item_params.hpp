#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct BeginTabItemParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<bool*> p_open = ParameterBase<bool*>("p_open", ParameterType::OUTPUT);
    ParameterBase<ImGuiTabItemFlags> flags = ParameterBase<ImGuiTabItemFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    BeginTabItemParams() = default;
};
