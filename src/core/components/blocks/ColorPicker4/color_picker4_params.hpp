#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ColorPicker4Params {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiColorEditFlags> flags = ParameterBase<ImGuiColorEditFlags>("flags", ParameterType::INPUT);
    ParameterBase<const float*> ref_col = ParameterBase<const float*>("ref_col", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    ColorPicker4Params() = default;
};
