#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct OpenPopupParams {
    ParameterBase<ImGuiID> id = ParameterBase<ImGuiID>("id", ParameterType::INPUT);
    ParameterBase<ImGuiPopupFlags> popup_flags = ParameterBase<ImGuiPopupFlags>("popup_flags", ParameterType::INPUT);

    OpenPopupParams() = default;
};
