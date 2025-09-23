#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct BeginTabItemParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<bool*> p_open = ParameterBase<bool*>("p_open", ParameterType::OUTPUT);
    ParameterBase<ImGuiTabItemFlags> flags = ParameterBase<ImGuiTabItemFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    BeginTabItemParams() {
        params.push_back(&label);
        params.push_back(&p_open);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
