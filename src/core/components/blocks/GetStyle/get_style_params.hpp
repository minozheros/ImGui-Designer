#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetStyleParams {
    ParameterBase<ImGuiStyle&> return_value = ParameterBase<ImGuiStyle&>("return_value", ParameterType::RETURN);

    GetStyleParams() = default;
};
