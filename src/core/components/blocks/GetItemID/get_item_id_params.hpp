#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetItemIDParams {
    ParameterBase<ImGuiID> return_value = ParameterBase<ImGuiID>("return_value", ParameterType::RETURN);

    GetItemIDParams() = default;
};
