#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct IsMouseReleasedWithDelayParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);
    ParameterBase<float> delay = ParameterBase<float>("delay", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    IsMouseReleasedWithDelayParams() {
        params.push_back(&button);
        params.push_back(&delay);
        params.push_back(&return_value);
    }
};
}
