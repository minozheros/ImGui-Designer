#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetScrollHereXParams : public core::IParameterParamsBase {
    ParameterBase<float> center_x_ratio = ParameterBase<float>("center_x_ratio", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetScrollHereXParams() {
        params.push_back(&center_x_ratio);
    }
};
}
