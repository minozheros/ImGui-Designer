#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TableSetupColumnParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiTableColumnFlags> flags = ParameterBase<ImGuiTableColumnFlags>("flags", ParameterType::INPUT);
    ParameterBase<float> init_width_or_weight = ParameterBase<float>("init_width_or_weight", ParameterType::INPUT);
    ParameterBase<ImGuiID> user_id = ParameterBase<ImGuiID>("user_id", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    TableSetupColumnParams() {
        params.push_back(&label);
        params.push_back(&flags);
        params.push_back(&init_width_or_weight);
        params.push_back(&user_id);
    }
};
}
