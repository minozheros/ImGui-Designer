#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct MenuItemParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const char*> shortcut = ParameterBase<const char*>("shortcut", ParameterType::INPUT);
    ParameterBase<bool*> p_selected = ParameterBase<bool*>("p_selected", ParameterType::OUTPUT);
    ParameterBase<bool> enabled = ParameterBase<bool>("enabled", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    MenuItemParams() = default;
};
