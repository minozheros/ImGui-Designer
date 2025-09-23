#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetWindowCollapsedParams : public core::IParameterParamsBase {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);
    ParameterBase<bool> collapsed = ParameterBase<bool>("collapsed", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetWindowCollapsedParams() {
        params.push_back(&name);
        params.push_back(&collapsed);
        params.push_back(&cond);
    }
};
}
