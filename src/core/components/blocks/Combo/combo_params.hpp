#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ComboParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<int*> current_item = ParameterBase<int*>("current_item", ParameterType::INPUT);
    ParameterBase<const char*> items_separated_by_zeros = ParameterBase<const char*>("items_separated_by_zeros", ParameterType::INPUT);
    ParameterBase<int> popup_max_height_in_items = ParameterBase<int>("popup_max_height_in_items", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    ComboParams() = default;
};
