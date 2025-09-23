#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetNextWindowClassParams : public core::IParameterParamsBase {
    ParameterBase<const ImGuiWindowClass*> window_class = ParameterBase<const ImGuiWindowClass*>("window_class", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowClassParams() {
        params.push_back(&window_class);
    }
};
}
