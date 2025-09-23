#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetDrawListSharedDataParams {
    ParameterBase<ImDrawListSharedData*> return_value = ParameterBase<ImDrawListSharedData*>("return_value", ParameterType::RETURN);

    GetDrawListSharedDataParams() = default;
};
