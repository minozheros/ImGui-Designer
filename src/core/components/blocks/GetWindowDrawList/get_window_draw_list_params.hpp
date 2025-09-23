#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetWindowDrawListParams {
    ParameterBase<ImDrawList*> return_value = ParameterBase<ImDrawList*>("return_value", ParameterType::RETURN);

    GetWindowDrawListParams() = default;
};
