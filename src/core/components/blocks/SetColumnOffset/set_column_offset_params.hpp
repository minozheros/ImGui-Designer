#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetColumnOffsetParams {
    ParameterBase<int> column_index = ParameterBase<int>("column_index", ParameterType::INPUT);
    ParameterBase<float> offset_x = ParameterBase<float>("offset_x", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetColumnOffsetParams() {
        params.push_back(&column_index);
        params.push_back(&offset_x);
    }
};
}
