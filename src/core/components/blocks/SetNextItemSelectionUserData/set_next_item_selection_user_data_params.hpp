#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextItemSelectionUserDataParams {
    ParameterBase<ImGuiSelectionUserData> selection_user_data = ParameterBase<ImGuiSelectionUserData>("selection_user_data", ParameterType::INPUT);

    SetNextItemSelectionUserDataParams() = default;
};
