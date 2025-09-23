#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct TableGetSortSpecsParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiTableSortSpecs*> return_value = ParameterBase<ImGuiTableSortSpecs*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    TableGetSortSpecsParams() {
        params.push_back(&return_value);
    }
};
}
