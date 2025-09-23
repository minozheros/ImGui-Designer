#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct TableNextRowParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiTableRowFlags> row_flags = ParameterBase<ImGuiTableRowFlags>("row_flags", ParameterType::INPUT);
    ParameterBase<float> min_row_height = ParameterBase<float>("min_row_height", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    TableNextRowParams() {
        params.push_back(&row_flags);
        params.push_back(&min_row_height);
    }
};
}
