#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ListBoxParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<int*> current_item = ParameterBase<int*>("current_item", ParameterType::INPUT);
    ParameterBase<int> items_count = ParameterBase<int>("items_count", ParameterType::INPUT);
    ParameterBase<int> height_in_items = ParameterBase<int>("height_in_items", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    ListBoxParams() {
        params.push_back(&label);
        params.push_back(&current_item);
        params.push_back(&items_count);
        params.push_back(&height_in_items);
        params.push_back(&return_value);
    }
};
}
