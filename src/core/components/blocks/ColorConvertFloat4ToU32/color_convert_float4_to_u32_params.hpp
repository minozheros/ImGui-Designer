#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ColorConvertFloat4ToU32Params {
    ParameterBase<const ImVec4&> in = ParameterBase<const ImVec4&>("in", ParameterType::INPUT);
    ParameterBase<ImU32> return_value = ParameterBase<ImU32>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    ColorConvertFloat4ToU32Params() {
        params.push_back(&in);
        params.push_back(&return_value);
    }
};
}
