#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct BeginTabBarParams {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<ImGuiTabBarFlags> flags = ParameterBase<ImGuiTabBarFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    BeginTabBarParams() = default;
};
