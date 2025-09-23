#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableGetSortSpecsParams {
    ParameterBase<ImGuiTableSortSpecs*> return_value = ParameterBase<ImGuiTableSortSpecs*>("return_value", ParameterType::RETURN);

    TableGetSortSpecsParams() = default;
};
