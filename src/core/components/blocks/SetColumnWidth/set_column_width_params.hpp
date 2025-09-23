#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetColumnWidthParams {
    ParameterBase<int> column_index = ParameterBase<int>("column_index", ParameterType::INPUT);
    ParameterBase<float> width = ParameterBase<float>("width", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetColumnWidthParams() {
        params.push_back(&column_index);
        params.push_back(&width);
    }
};
}
