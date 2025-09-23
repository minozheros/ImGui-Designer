#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetPlatformIOParams {
    ParameterBase<ImGuiPlatformIO&> return_value = ParameterBase<ImGuiPlatformIO&>("return_value", ParameterType::RETURN);

    GetPlatformIOParams() = default;
};
