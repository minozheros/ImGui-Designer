#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TableGetSortSpecsParams {
    ParameterBase<ImGuiTableSortSpecs*> return_value = ParameterBase<ImGuiTableSortSpecs*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    TableGetSortSpecsParams() {
        params.push_back(&return_value);
    }
};
}
