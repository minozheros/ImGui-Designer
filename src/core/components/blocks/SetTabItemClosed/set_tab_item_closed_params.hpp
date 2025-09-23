#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetTabItemClosedParams : public core::IParameterParamsBase {
    ParameterBase<const char*> tab_or_docked_window_label = ParameterBase<const char*>("tab_or_docked_window_label", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetTabItemClosedParams() {
        params.push_back(&tab_or_docked_window_label);
    }
};
}
