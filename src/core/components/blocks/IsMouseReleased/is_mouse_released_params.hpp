#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct IsMouseReleasedParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    IsMouseReleasedParams() {
        params.push_back(&button);
        params.push_back(&return_value);
    }
};
}
