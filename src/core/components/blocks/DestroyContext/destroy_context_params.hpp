#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct DestroyContextParams {
    ParameterBase<ImGuiContext*> ctx = ParameterBase<ImGuiContext*>("ctx", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    DestroyContextParams() {
        params.push_back(&ctx);
    }
};
}
