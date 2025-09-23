#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct InputFloat4Params {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    InputFloat4Params() = default;
};
