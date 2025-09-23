#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetIDParams {
    ParameterBase<int> int_id = ParameterBase<int>("int_id", ParameterType::INPUT);
    ParameterBase<ImGuiID> return_value = ParameterBase<ImGuiID>("return_value", ParameterType::RETURN);

    GetIDParams() = default;
};
