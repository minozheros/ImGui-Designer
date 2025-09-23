#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetItemIDParams {
    ParameterBase<ImGuiID> return_value = ParameterBase<ImGuiID>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetItemIDParams() {
        params.push_back(&return_value);
    }
};
}
