#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ShowMetricsWindowParams {
    ParameterBase<bool*> p_open = ParameterBase<bool*>("p_open", ParameterType::OUTPUT);

    std::vector<core::IParameterBase*> params;
    ShowMetricsWindowParams() {
        params.push_back(&p_open);
    }
};
}
