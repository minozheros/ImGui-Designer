#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextItemOpenParams {
    ParameterBase<bool> is_open = ParameterBase<bool>("is_open", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextItemOpenParams() {
        params.push_back(&is_open);
        params.push_back(&cond);
    }
};
}
