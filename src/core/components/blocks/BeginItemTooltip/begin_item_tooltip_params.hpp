#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct BeginItemTooltipParams {
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    BeginItemTooltipParams() {
        params.push_back(&return_value);
    }
};
}
