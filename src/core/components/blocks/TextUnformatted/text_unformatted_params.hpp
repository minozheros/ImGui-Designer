#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TextUnformattedParams {
    ParameterBase<const char*> text = ParameterBase<const char*>("text", ParameterType::INPUT);
    ParameterBase<const char*> text_end = ParameterBase<const char*>("text_end", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    TextUnformattedParams() {
        params.push_back(&text);
        params.push_back(&text_end);
    }
};
}
