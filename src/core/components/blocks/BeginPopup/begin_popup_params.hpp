#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct BeginPopupParams {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<ImGuiWindowFlags> flags = ParameterBase<ImGuiWindowFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    BeginPopupParams() = default;
};
