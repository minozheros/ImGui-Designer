#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TextLinkOpenURLParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const char*> url = ParameterBase<const char*>("url", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    TextLinkOpenURLParams() = default;
};
