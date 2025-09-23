#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetScrollFromPosYParams {
    ParameterBase<float> local_y = ParameterBase<float>("local_y", ParameterType::INPUT);
    ParameterBase<float> center_y_ratio = ParameterBase<float>("center_y_ratio", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetScrollFromPosYParams() {
        params.push_back(&local_y);
        params.push_back(&center_y_ratio);
    }
};
}
