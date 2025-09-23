#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TableGetColumnCountParams {
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    TableGetColumnCountParams() {
        params.push_back(&return_value);
    }
};
}
