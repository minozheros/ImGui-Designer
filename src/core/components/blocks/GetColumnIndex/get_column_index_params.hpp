#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetColumnIndexParams {
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    GetColumnIndexParams() = default;
};
