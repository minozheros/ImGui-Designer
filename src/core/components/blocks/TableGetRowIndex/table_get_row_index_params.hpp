#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TableGetRowIndexParams {
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    TableGetRowIndexParams() {
        params.push_back(&return_value);
    }
};
}
