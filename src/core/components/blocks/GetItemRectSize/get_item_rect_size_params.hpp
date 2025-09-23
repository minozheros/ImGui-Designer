#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetItemRectSizeParams {
    ParameterBase<ImVec2> return_value = ParameterBase<ImVec2>("return_value", ParameterType::RETURN);

    GetItemRectSizeParams() = default;
};
