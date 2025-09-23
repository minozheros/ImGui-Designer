#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ColorPicker4Params {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<ImGuiColorEditFlags> flags = ParameterBase<ImGuiColorEditFlags>("flags", ParameterType::INPUT);
    ParameterBase<const float*> ref_col = ParameterBase<const float*>("ref_col", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    ColorPicker4Params() {
        params.push_back(&label);
        params.push_back(&flags);
        params.push_back(&ref_col);
        params.push_back(&return_value);
    }
};
}
