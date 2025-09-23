#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableNextRowParams {
    ParameterBase<ImGuiTableRowFlags> row_flags = ParameterBase<ImGuiTableRowFlags>("row_flags", ParameterType::INPUT);
    ParameterBase<float> min_row_height = ParameterBase<float>("min_row_height", ParameterType::INPUT);

    TableNextRowParams() = default;
};
