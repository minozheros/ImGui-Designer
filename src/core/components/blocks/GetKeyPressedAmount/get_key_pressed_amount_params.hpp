#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetKeyPressedAmountParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiKey> key = ParameterBase<ImGuiKey>("key", ParameterType::INPUT);
    ParameterBase<float> repeat_delay = ParameterBase<float>("repeat_delay", ParameterType::INPUT);
    ParameterBase<float> rate = ParameterBase<float>("rate", ParameterType::INPUT);
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetKeyPressedAmountParams() {
        params.push_back(&key);
        params.push_back(&repeat_delay);
        params.push_back(&rate);
        params.push_back(&return_value);
    }
};
}
