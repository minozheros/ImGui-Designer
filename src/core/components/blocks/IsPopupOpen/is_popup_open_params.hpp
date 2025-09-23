#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsPopupOpenParams {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<ImGuiPopupFlags> flags = ParameterBase<ImGuiPopupFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsPopupOpenParams() = default;
};
