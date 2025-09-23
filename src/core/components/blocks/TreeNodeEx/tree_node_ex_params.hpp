#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TreeNodeExParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiTreeNodeFlags> flags = ParameterBase<ImGuiTreeNodeFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    TreeNodeExParams() = default;
};
