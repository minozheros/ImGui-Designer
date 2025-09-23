#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetColumnIndexParams {
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetColumnIndexParams() {
        params.push_back(&return_value);
    }
};
}
