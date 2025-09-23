#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ListBoxParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<int*> current_item = ParameterBase<int*>("current_item", ParameterType::INPUT);
    ParameterBase<int> items_count = ParameterBase<int>("items_count", ParameterType::INPUT);
    ParameterBase<int> height_in_items = ParameterBase<int>("height_in_items", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    ListBoxParams() = default;
};
