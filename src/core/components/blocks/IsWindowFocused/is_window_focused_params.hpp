#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct IsWindowFocusedParams {
    ParameterBase<ImGuiFocusedFlags> flags = ParameterBase<ImGuiFocusedFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    IsWindowFocusedParams() {
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
