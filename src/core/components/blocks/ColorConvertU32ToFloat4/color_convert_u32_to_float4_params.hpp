#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ColorConvertU32ToFloat4Params {
    ParameterBase<ImU32> in = ParameterBase<ImU32>("in", ParameterType::INPUT);
    ParameterBase<ImVec4> return_value = ParameterBase<ImVec4>("return_value", ParameterType::RETURN);

    ColorConvertU32ToFloat4Params() = default;
};
