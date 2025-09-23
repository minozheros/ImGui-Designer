#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct CollapsingHeaderParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<bool*> p_visible = ParameterBase<bool*>("p_visible", ParameterType::OUTPUT);
    ParameterBase<ImGuiTreeNodeFlags> flags = ParameterBase<ImGuiTreeNodeFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    CollapsingHeaderParams() = default;
};
