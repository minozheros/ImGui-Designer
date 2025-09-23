#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetFontParams {
    ParameterBase<ImFont*> return_value = ParameterBase<ImFont*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetFontParams() {
        params.push_back(&return_value);
    }
};
}
