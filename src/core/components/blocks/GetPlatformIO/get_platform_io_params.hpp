#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetPlatformIOParams {
    ParameterBase<ImGuiPlatformIO&> return_value = ParameterBase<ImGuiPlatformIO&>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetPlatformIOParams() {
        params.push_back(&return_value);
    }
};
}
