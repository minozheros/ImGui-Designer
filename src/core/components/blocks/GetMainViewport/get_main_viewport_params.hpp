#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetMainViewportParams {
    ParameterBase<ImGuiViewport*> return_value = ParameterBase<ImGuiViewport*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetMainViewportParams() {
        params.push_back(&return_value);
    }
};
}
