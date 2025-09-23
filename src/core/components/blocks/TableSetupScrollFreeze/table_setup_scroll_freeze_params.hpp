#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TableSetupScrollFreezeParams {
    ParameterBase<int> cols = ParameterBase<int>("cols", ParameterType::INPUT);
    ParameterBase<int> rows = ParameterBase<int>("rows", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    TableSetupScrollFreezeParams() {
        params.push_back(&cols);
        params.push_back(&rows);
    }
};
}
