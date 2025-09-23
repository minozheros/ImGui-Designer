#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>
namespace core
{

    struct BeginComboParams
    {
        ParameterBase<const char *> label = ParameterBase<const char *>("label", ParameterType::INPUT);
        ParameterBase<const char *> preview_value = ParameterBase<const char *>("preview_value", ParameterType::INPUT);
        ParameterBase<ImGuiComboFlags> flags = ParameterBase<ImGuiComboFlags>("flags", ParameterType::INPUT);
        ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

        BeginComboParams() = default;
    };
}