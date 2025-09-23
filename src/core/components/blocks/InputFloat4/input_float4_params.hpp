#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct InputFloat4Params : public core::IParameterParamsBase {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    InputFloat4Params() {
        params.push_back(&label);
        params.push_back(&format);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
