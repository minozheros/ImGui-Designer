#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct RenderPlatformWindowsDefaultParams {
    ParameterBase<void*> platform_render_arg = ParameterBase<void*>("platform_render_arg", ParameterType::INPUT);
    ParameterBase<void*> renderer_render_arg = ParameterBase<void*>("renderer_render_arg", ParameterType::INPUT);

    RenderPlatformWindowsDefaultParams() = default;
};
