#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct InputInt3Params {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    InputInt3Params() {
        params.push_back(&label);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
