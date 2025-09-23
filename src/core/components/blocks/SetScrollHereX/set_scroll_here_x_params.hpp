#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetScrollHereXParams {
    ParameterBase<float> center_x_ratio = ParameterBase<float>("center_x_ratio", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetScrollHereXParams() {
        params.push_back(&center_x_ratio);
    }
};
}
