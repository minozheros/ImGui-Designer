#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct ResetMouseDragDeltaParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    ResetMouseDragDeltaParams() {
        params.push_back(&button);
    }
};
}
