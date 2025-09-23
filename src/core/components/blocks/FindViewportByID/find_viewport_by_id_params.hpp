#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct FindViewportByIDParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiID> id = ParameterBase<ImGuiID>("id", ParameterType::INPUT);
    ParameterBase<ImGuiViewport*> return_value = ParameterBase<ImGuiViewport*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    FindViewportByIDParams() {
        params.push_back(&id);
        params.push_back(&return_value);
    }
};
}
