#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct BeginMultiSelectParams {
    ParameterBase<ImGuiMultiSelectFlags> flags = ParameterBase<ImGuiMultiSelectFlags>("flags", ParameterType::INPUT);
    ParameterBase<int> selection_size = ParameterBase<int>("selection_size", ParameterType::INPUT);
    ParameterBase<int> items_count = ParameterBase<int>("items_count", ParameterType::INPUT);
    ParameterBase<ImGuiMultiSelectIO*> return_value = ParameterBase<ImGuiMultiSelectIO*>("return_value", ParameterType::RETURN);

    BeginMultiSelectParams() = default;
};
