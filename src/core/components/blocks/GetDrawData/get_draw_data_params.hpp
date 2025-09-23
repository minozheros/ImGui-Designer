#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetDrawDataParams {
    ParameterBase<ImDrawData*> return_value = ParameterBase<ImDrawData*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetDrawDataParams() {
        params.push_back(&return_value);
    }
};
}
