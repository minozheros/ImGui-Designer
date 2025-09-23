#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetFontBakedParams {
    ParameterBase<ImFontBaked*> return_value = ParameterBase<ImFontBaked*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetFontBakedParams() {
        params.push_back(&return_value);
    }
};
}
