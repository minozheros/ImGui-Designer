#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct InvisibleButtonParams {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<const ImVec2&> size = ParameterBase<const ImVec2&>("size", ParameterType::INPUT);
    ParameterBase<ImGuiButtonFlags> flags = ParameterBase<ImGuiButtonFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    InvisibleButtonParams() {
        params.push_back(&str_id);
        params.push_back(&size);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
