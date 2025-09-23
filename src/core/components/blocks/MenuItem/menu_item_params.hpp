#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct MenuItemParams : public core::IParameterParamsBase {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const char*> shortcut = ParameterBase<const char*>("shortcut", ParameterType::INPUT);
    ParameterBase<bool*> p_selected = ParameterBase<bool*>("p_selected", ParameterType::OUTPUT);
    ParameterBase<bool> enabled = ParameterBase<bool>("enabled", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    MenuItemParams() {
        params.push_back(&label);
        params.push_back(&shortcut);
        params.push_back(&p_selected);
        params.push_back(&enabled);
        params.push_back(&return_value);
    }
};
}
