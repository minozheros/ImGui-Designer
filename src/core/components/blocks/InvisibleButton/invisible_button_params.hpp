#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct InvisibleButtonParams {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<const ImVec2&> size = ParameterBase<const ImVec2&>("size", ParameterType::INPUT);
    ParameterBase<ImGuiButtonFlags> flags = ParameterBase<ImGuiButtonFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    InvisibleButtonParams() = default;
};
