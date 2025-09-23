#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct PushItemFlagParams {
    ParameterBase<ImGuiItemFlags> option = ParameterBase<ImGuiItemFlags>("option", ParameterType::INPUT);
    ParameterBase<bool> enabled = ParameterBase<bool>("enabled", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushItemFlagParams() {
        params.push_back(&option);
        params.push_back(&enabled);
    }
};
}
