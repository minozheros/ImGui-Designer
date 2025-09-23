#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct PushItemFlagParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiItemFlags> option = ParameterBase<ImGuiItemFlags>("option", ParameterType::INPUT);
    ParameterBase<bool> enabled = ParameterBase<bool>("enabled", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushItemFlagParams() {
        params.push_back(&option);
        params.push_back(&enabled);
    }
};
}
