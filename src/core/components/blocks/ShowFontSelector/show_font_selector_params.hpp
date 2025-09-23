#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ShowFontSelectorParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);

    ShowFontSelectorParams() = default;
};
