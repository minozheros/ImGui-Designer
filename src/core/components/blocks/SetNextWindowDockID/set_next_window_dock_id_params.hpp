#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetNextWindowDockIDParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiID> dock_id = ParameterBase<ImGuiID>("dock_id", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowDockIDParams() {
        params.push_back(&dock_id);
        params.push_back(&cond);
    }
};
}
