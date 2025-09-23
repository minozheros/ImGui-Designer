#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct EndMultiSelectParams {
    ParameterBase<ImGuiMultiSelectIO*> return_value = ParameterBase<ImGuiMultiSelectIO*>("return_value", ParameterType::RETURN);

    EndMultiSelectParams() = default;
};
