#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct FindViewportByIDParams {
    ParameterBase<ImGuiID> id = ParameterBase<ImGuiID>("id", ParameterType::INPUT);
    ParameterBase<ImGuiViewport*> return_value = ParameterBase<ImGuiViewport*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    FindViewportByIDParams() {
        params.push_back(&id);
        params.push_back(&return_value);
    }
};
}
