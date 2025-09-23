#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetWindowPosParams {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);
    ParameterBase<const ImVec2&> pos = ParameterBase<const ImVec2&>("pos", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetWindowPosParams() {
        params.push_back(&name);
        params.push_back(&pos);
        params.push_back(&cond);
    }
};
}
