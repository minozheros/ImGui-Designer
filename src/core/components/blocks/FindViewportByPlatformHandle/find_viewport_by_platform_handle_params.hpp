#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct FindViewportByPlatformHandleParams {
    ParameterBase<void*> platform_handle = ParameterBase<void*>("platform_handle", ParameterType::INPUT);
    ParameterBase<ImGuiViewport*> return_value = ParameterBase<ImGuiViewport*>("return_value", ParameterType::RETURN);

    FindViewportByPlatformHandleParams() = default;
};
