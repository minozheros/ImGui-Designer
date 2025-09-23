#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct EndMultiSelectParams {
    ParameterBase<ImGuiMultiSelectIO*> return_value = ParameterBase<ImGuiMultiSelectIO*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    EndMultiSelectParams() {
        params.push_back(&return_value);
    }
};
}
