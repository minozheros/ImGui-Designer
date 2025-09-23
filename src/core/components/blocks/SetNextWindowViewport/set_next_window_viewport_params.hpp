#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextWindowViewportParams {
    ParameterBase<ImGuiID> viewport_id = ParameterBase<ImGuiID>("viewport_id", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowViewportParams() {
        params.push_back(&viewport_id);
    }
};
}
