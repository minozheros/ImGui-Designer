#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct FindViewportByPlatformHandleParams {
    ParameterBase<void*> platform_handle = ParameterBase<void*>("platform_handle", ParameterType::INPUT);
    ParameterBase<ImGuiViewport*> return_value = ParameterBase<ImGuiViewport*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    FindViewportByPlatformHandleParams() {
        params.push_back(&platform_handle);
        params.push_back(&return_value);
    }
};
}
