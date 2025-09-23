#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetScrollYParams : public core::IParameterParamsBase {
    ParameterBase<float> scroll_y = ParameterBase<float>("scroll_y", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetScrollYParams() {
        params.push_back(&scroll_y);
    }
};
}
