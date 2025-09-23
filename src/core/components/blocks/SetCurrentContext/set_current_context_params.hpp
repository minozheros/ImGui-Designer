#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetCurrentContextParams {
    ParameterBase<ImGuiContext*> ctx = ParameterBase<ImGuiContext*>("ctx", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetCurrentContextParams() {
        params.push_back(&ctx);
    }
};
}
