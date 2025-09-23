#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetNextWindowViewportParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiID> viewport_id = ParameterBase<ImGuiID>("viewport_id", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowViewportParams() {
        params.push_back(&viewport_id);
    }
};
}
