#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsMousePosValidParams {
    ParameterBase<const ImVec2*> mouse_pos = ParameterBase<const ImVec2*>("mouse_pos", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsMousePosValidParams() = default;
};
