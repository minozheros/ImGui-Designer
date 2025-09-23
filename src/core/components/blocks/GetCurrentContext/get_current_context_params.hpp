#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetCurrentContextParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiContext*> return_value = ParameterBase<ImGuiContext*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetCurrentContextParams() {
        params.push_back(&return_value);
    }
};
}
