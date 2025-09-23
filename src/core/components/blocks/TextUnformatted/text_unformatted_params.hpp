#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TextUnformattedParams {
    ParameterBase<const char*> text = ParameterBase<const char*>("text", ParameterType::INPUT);
    ParameterBase<const char*> text_end = ParameterBase<const char*>("text_end", ParameterType::INPUT);

    TextUnformattedParams() = default;
};
