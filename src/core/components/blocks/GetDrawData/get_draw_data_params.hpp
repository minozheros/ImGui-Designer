#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetDrawDataParams {
    ParameterBase<ImDrawData*> return_value = ParameterBase<ImDrawData*>("return_value", ParameterType::RETURN);

    GetDrawDataParams() = default;
};
