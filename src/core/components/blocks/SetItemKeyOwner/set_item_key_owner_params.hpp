#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetItemKeyOwnerParams {
    ParameterBase<ImGuiKey> key = ParameterBase<ImGuiKey>("key", ParameterType::INPUT);

    SetItemKeyOwnerParams() = default;
};
