#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetScrollFromPosXParams : public core::IParameterParamsBase {
    ParameterBase<float> local_x = ParameterBase<float>("local_x", ParameterType::INPUT);
    ParameterBase<float> center_x_ratio = ParameterBase<float>("center_x_ratio", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetScrollFromPosXParams() {
        params.push_back(&local_x);
        params.push_back(&center_x_ratio);
    }
};
}
