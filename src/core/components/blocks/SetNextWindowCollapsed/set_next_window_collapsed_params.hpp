#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextWindowCollapsedParams {
    ParameterBase<bool> collapsed = ParameterBase<bool>("collapsed", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowCollapsedParams() {
        params.push_back(&collapsed);
        params.push_back(&cond);
    }
};
}
