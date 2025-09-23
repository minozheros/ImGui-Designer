#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushItemFlagParams {
    ParameterBase<ImGuiItemFlags> option = ParameterBase<ImGuiItemFlags>("option", ParameterType::INPUT);
    ParameterBase<bool> enabled = ParameterBase<bool>("enabled", ParameterType::INPUT);

    PushItemFlagParams() = default;
};
