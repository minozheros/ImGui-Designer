#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextWindowSizeConstraintsParams {
    ParameterBase<const ImVec2&> size_min = ParameterBase<const ImVec2&>("size_min", ParameterType::INPUT);
    ParameterBase<const ImVec2&> size_max = ParameterBase<const ImVec2&>("size_max", ParameterType::INPUT);
    ParameterBase<ImGuiSizeCallback> custom_callback = ParameterBase<ImGuiSizeCallback>("custom_callback", ParameterType::INPUT);
    ParameterBase<void*> custom_callback_data = ParameterBase<void*>("custom_callback_data", ParameterType::INPUT);

    SetNextWindowSizeConstraintsParams() = default;
};
