#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ResetMouseDragDeltaParams {
    ParameterBase<ImGuiMouseButton> button = ParameterBase<ImGuiMouseButton>("button", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    ResetMouseDragDeltaParams() {
        params.push_back(&button);
    }
};
}
