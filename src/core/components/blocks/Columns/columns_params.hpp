#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ColumnsParams {
    ParameterBase<int> count = ParameterBase<int>("count", ParameterType::INPUT);
    ParameterBase<const char*> id = ParameterBase<const char*>("id", ParameterType::INPUT);
    ParameterBase<bool> borders = ParameterBase<bool>("borders", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    ColumnsParams() {
        params.push_back(&count);
        params.push_back(&id);
        params.push_back(&borders);
    }
};
}
