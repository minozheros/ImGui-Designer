#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetStateStorageParams {
    ParameterBase<ImGuiStorage*> storage = ParameterBase<ImGuiStorage*>("storage", ParameterType::INPUT);

    SetStateStorageParams() = default;
};
