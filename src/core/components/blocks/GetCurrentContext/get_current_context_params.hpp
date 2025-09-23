#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetCurrentContextParams {
    ParameterBase<ImGuiContext*> return_value = ParameterBase<ImGuiContext*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetCurrentContextParams() {
        params.push_back(&return_value);
    }
};
}
