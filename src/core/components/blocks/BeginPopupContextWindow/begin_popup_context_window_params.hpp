#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct BeginPopupContextWindowParams {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<ImGuiPopupFlags> popup_flags = ParameterBase<ImGuiPopupFlags>("popup_flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    BeginPopupContextWindowParams() = default;
};
