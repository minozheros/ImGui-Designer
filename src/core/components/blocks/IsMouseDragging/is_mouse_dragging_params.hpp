#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct IsMouseDraggingParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<float> lock_threshold = ParameterBase<float>("lock_threshold", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    IsMouseDraggingParams() {
        params.push_back(&button);
        params.push_back(&lock_threshold);
        params.push_back(&return_value);
    }
};
}
