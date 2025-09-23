#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TreeNodeParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    TreeNodeParams() = default;
};
