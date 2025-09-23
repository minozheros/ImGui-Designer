#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ColorConvertFloat4ToU32Params {
    ParameterBase<const ImVec4&> in = ParameterBase<const ImVec4&>("in", ParameterType::INPUT);
    ParameterBase<ImU32> return_value = ParameterBase<ImU32>("return_value", ParameterType::RETURN);

    ColorConvertFloat4ToU32Params() = default;
};
