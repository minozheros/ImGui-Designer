#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct BeginComboParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const char*> preview_value = ParameterBase<const char*>("preview_value", ParameterType::INPUT);
    ParameterBase<ImGuiComboFlags> flags = ParameterBase<ImGuiComboFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    BeginComboParams() {
        params.push_back(&label);
        params.push_back(&preview_value);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
