#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetScrollHereYParams : public core::IParameterParamsBase {
    ParameterBase<float> center_y_ratio = ParameterBase<float>("center_y_ratio", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetScrollHereYParams() {
        params.push_back(&center_y_ratio);
    }
};
}
