#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetFontSizeParams {
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetFontSizeParams() {
        params.push_back(&return_value);
    }
};
}
