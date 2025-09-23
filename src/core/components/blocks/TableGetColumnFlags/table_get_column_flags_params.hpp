#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TableGetColumnFlagsParams {
    ParameterBase<int> column_n = ParameterBase<int>("column_n", ParameterType::INPUT);
    ParameterBase<ImGuiTableColumnFlags> return_value = ParameterBase<ImGuiTableColumnFlags>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    TableGetColumnFlagsParams() {
        params.push_back(&column_n);
        params.push_back(&return_value);
    }
};
}
