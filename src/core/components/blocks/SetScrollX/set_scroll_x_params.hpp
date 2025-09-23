#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetScrollXParams : public core::IParameterParamsBase {
    ParameterBase<float> scroll_x = ParameterBase<float>("scroll_x", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetScrollXParams() {
        params.push_back(&scroll_x);
    }
};
}
