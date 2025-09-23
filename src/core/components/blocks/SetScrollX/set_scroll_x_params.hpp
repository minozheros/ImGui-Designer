#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetScrollXParams {
    ParameterBase<float> scroll_x = ParameterBase<float>("scroll_x", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetScrollXParams() {
        params.push_back(&scroll_x);
    }
};
}
