#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableSetBgColorParams {
    ParameterBase<ImGuiTableBgTarget> target = ParameterBase<ImGuiTableBgTarget>("target", ParameterType::INPUT);
    ParameterBase<ImU32> color = ParameterBase<ImU32>("color", ParameterType::INPUT);
    ParameterBase<int> column_n = ParameterBase<int>("column_n", ParameterType::INPUT);

    TableSetBgColorParams() = default;
};
