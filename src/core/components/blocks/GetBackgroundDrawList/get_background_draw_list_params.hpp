#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetBackgroundDrawListParams {
    ParameterBase<ImGuiViewport*> viewport = ParameterBase<ImGuiViewport*>("viewport", ParameterType::INPUT);
    ParameterBase<ImDrawList*> return_value = ParameterBase<ImDrawList*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetBackgroundDrawListParams() {
        params.push_back(&viewport);
        params.push_back(&return_value);
    }
};
}
