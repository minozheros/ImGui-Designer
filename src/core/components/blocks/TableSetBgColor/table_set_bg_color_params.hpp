#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TableSetBgColorParams {
    ParameterBase<ImGuiTableBgTarget> target = ParameterBase<ImGuiTableBgTarget>("target", ParameterType::INPUT);
    ParameterBase<ImU32> color = ParameterBase<ImU32>("color", ParameterType::INPUT);
    ParameterBase<int> column_n = ParameterBase<int>("column_n", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    TableSetBgColorParams() {
        params.push_back(&target);
        params.push_back(&color);
        params.push_back(&column_n);
    }
};
}
