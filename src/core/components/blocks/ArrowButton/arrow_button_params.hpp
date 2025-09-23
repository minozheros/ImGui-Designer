#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ArrowButtonParams {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<ImGuiDir> dir = ParameterBase<ImGuiDir>("dir", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    ArrowButtonParams() = default;
};
