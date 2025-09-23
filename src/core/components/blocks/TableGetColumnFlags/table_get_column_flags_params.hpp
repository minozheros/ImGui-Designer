#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableGetColumnFlagsParams {
    ParameterBase<int> column_n = ParameterBase<int>("column_n", ParameterType::INPUT);
    ParameterBase<ImGuiTableColumnFlags> return_value = ParameterBase<ImGuiTableColumnFlags>("return_value", ParameterType::RETURN);

    TableGetColumnFlagsParams() = default;
};
