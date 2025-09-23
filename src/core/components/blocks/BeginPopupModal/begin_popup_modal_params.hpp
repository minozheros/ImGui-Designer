#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct BeginPopupModalParams : public core::IParameterParamsBase {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);
    ParameterBase<bool*> p_open = ParameterBase<bool*>("p_open", ParameterType::OUTPUT);
    ParameterBase<ImGuiWindowFlags> flags = ParameterBase<ImGuiWindowFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    BeginPopupModalParams() {
        params.push_back(&name);
        params.push_back(&p_open);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
