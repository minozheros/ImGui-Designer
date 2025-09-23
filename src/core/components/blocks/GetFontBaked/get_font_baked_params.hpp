#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetFontBakedParams {
    ParameterBase<ImFontBaked*> return_value = ParameterBase<ImFontBaked*>("return_value", ParameterType::RETURN);

    GetFontBakedParams() = default;
};
