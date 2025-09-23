#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct DebugTextEncodingParams {
    ParameterBase<const char*> text = ParameterBase<const char*>("text", ParameterType::INPUT);

    DebugTextEncodingParams() = default;
};
