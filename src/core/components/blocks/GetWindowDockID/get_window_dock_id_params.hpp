#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetWindowDockIDParams {
    ParameterBase<ImGuiID> return_value = ParameterBase<ImGuiID>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetWindowDockIDParams() {
        params.push_back(&return_value);
    }
};
}
