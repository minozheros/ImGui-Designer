#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetItemKeyOwnerParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiKey> key = ParameterBase<ImGuiKey>("key", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetItemKeyOwnerParams() {
        params.push_back(&key);
    }
};
}
