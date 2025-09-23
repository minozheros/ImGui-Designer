#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetItemKeyOwnerParams {
    ParameterBase<ImGuiKey> key = ParameterBase<ImGuiKey>("key", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetItemKeyOwnerParams() {
        params.push_back(&key);
    }
};
}
