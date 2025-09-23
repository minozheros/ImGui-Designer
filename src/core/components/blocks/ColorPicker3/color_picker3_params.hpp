#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ColorPicker3Params {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiColorEditFlags> flags = ParameterBase<ImGuiColorEditFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    ColorPicker3Params() = default;
};
