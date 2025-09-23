#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ColorConvertU32ToFloat4Params {
    ParameterBase<ImU32> in = ParameterBase<ImU32>("in", ParameterType::INPUT);
    ParameterBase<ImVec4> return_value = ParameterBase<ImVec4>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    ColorConvertU32ToFloat4Params() {
        params.push_back(&in);
        params.push_back(&return_value);
    }
};
}
