#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetItemIDParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiID> return_value = ParameterBase<ImGuiID>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetItemIDParams() {
        params.push_back(&return_value);
    }
};
}
