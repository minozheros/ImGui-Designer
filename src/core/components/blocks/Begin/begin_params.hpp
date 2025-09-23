#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct BeginParams {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);
    ParameterBase<bool*> p_open = ParameterBase<bool*>("p_open", ParameterType::OUTPUT);
    ParameterBase<ImGuiWindowFlags> flags = ParameterBase<ImGuiWindowFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    BeginParams() = default;
};
