#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetMouseDragDeltaParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<float> lock_threshold = ParameterBase<float>("lock_threshold", ParameterType::INPUT);
    ParameterBase<ImVec2> return_value = ParameterBase<ImVec2>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetMouseDragDeltaParams() {
        params.push_back(&button);
        params.push_back(&lock_threshold);
        params.push_back(&return_value);
    }
};
}
