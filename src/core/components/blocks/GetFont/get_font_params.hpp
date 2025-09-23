#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetFontParams {
    ParameterBase<ImFont*> return_value = ParameterBase<ImFont*>("return_value", ParameterType::RETURN);

    GetFontParams() = default;
};
