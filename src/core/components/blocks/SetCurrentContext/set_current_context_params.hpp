#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetCurrentContextParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiContext*> ctx = ParameterBase<ImGuiContext*>("ctx", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetCurrentContextParams() {
        params.push_back(&ctx);
    }
};
}
