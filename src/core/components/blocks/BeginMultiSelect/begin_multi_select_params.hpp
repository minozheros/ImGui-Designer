#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct BeginMultiSelectParams {
    ParameterBase<ImGuiMultiSelectFlags> flags = ParameterBase<ImGuiMultiSelectFlags>("flags", ParameterType::INPUT);
    ParameterBase<int> selection_size = ParameterBase<int>("selection_size", ParameterType::INPUT);
    ParameterBase<int> items_count = ParameterBase<int>("items_count", ParameterType::INPUT);
    ParameterBase<ImGuiMultiSelectIO*> return_value = ParameterBase<ImGuiMultiSelectIO*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    BeginMultiSelectParams() {
        params.push_back(&flags);
        params.push_back(&selection_size);
        params.push_back(&items_count);
        params.push_back(&return_value);
    }
};
}
