#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetColumnWidthParams {
    ParameterBase<int> column_index = ParameterBase<int>("column_index", ParameterType::INPUT);
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetColumnWidthParams() {
        params.push_back(&column_index);
        params.push_back(&return_value);
    }
};
}
