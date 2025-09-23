#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ShowFontSelectorParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    ShowFontSelectorParams() {
        params.push_back(&label);
    }
};
}
