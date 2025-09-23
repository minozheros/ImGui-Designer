#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetMouseClickedCountParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetMouseClickedCountParams() {
        params.push_back(&button);
        params.push_back(&return_value);
    }
};
}
