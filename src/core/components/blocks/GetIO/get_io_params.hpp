#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetIOParams {
    ParameterBase<ImGuiIO&> return_value = ParameterBase<ImGuiIO&>("return_value", ParameterType::RETURN);

    GetIOParams() = default;
};
