#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetStateStorageParams {
    ParameterBase<ImGuiStorage*> return_value = ParameterBase<ImGuiStorage*>("return_value", ParameterType::RETURN);

    GetStateStorageParams() = default;
};
