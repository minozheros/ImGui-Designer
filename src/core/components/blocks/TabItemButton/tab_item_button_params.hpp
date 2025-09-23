#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TabItemButtonParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiTabItemFlags> flags = ParameterBase<ImGuiTabItemFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    TabItemButtonParams() = default;
};
