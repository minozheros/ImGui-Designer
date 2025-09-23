#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableSetupColumnParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiTableColumnFlags> flags = ParameterBase<ImGuiTableColumnFlags>("flags", ParameterType::INPUT);
    ParameterBase<float> init_width_or_weight = ParameterBase<float>("init_width_or_weight", ParameterType::INPUT);
    ParameterBase<ImGuiID> user_id = ParameterBase<ImGuiID>("user_id", ParameterType::INPUT);

    TableSetupColumnParams() = default;
};
