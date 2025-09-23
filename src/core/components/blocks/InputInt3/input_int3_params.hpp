#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct InputInt3Params {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    InputInt3Params() = default;
};
