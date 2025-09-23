#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct RenderPlatformWindowsDefaultParams : public core::IParameterParamsBase {
    ParameterBase<void*> platform_render_arg = ParameterBase<void*>("platform_render_arg", ParameterType::INPUT);
    ParameterBase<void*> renderer_render_arg = ParameterBase<void*>("renderer_render_arg", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    RenderPlatformWindowsDefaultParams() {
        params.push_back(&platform_render_arg);
        params.push_back(&renderer_render_arg);
    }
};
}
