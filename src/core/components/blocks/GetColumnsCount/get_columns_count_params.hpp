#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetColumnsCountParams {
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetColumnsCountParams() {
        params.push_back(&return_value);
    }
};
}
