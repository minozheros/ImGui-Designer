#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextWindowSizeConstraintsParams {
    ParameterBase<const ImVec2&> size_min = ParameterBase<const ImVec2&>("size_min", ParameterType::INPUT);
    ParameterBase<const ImVec2&> size_max = ParameterBase<const ImVec2&>("size_max", ParameterType::INPUT);
    ParameterBase<ImGuiSizeCallback> custom_callback = ParameterBase<ImGuiSizeCallback>("custom_callback", ParameterType::INPUT);
    ParameterBase<void*> custom_callback_data = ParameterBase<void*>("custom_callback_data", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowSizeConstraintsParams() {
        params.push_back(&size_min);
        params.push_back(&size_max);
        params.push_back(&custom_callback);
        params.push_back(&custom_callback_data);
    }
};
}
