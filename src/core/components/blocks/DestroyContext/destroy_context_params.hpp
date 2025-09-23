#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct DestroyContextParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiContext*> ctx = ParameterBase<ImGuiContext*>("ctx", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    DestroyContextParams() {
        params.push_back(&ctx);
    }
};
}
