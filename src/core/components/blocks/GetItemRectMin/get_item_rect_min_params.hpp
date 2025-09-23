#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetItemRectMinParams {
    ParameterBase<ImVec2> return_value = ParameterBase<ImVec2>("return_value", ParameterType::RETURN);

    GetItemRectMinParams() = default;
};
