#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextItemStorageIDParams {
    ParameterBase<ImGuiID> storage_id = ParameterBase<ImGuiID>("storage_id", ParameterType::INPUT);

    SetNextItemStorageIDParams() = default;
};
