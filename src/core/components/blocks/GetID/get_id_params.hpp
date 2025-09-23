#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetIDParams {
    ParameterBase<int> int_id = ParameterBase<int>("int_id", ParameterType::INPUT);
    ParameterBase<ImGuiID> return_value = ParameterBase<ImGuiID>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetIDParams() {
        params.push_back(&int_id);
        params.push_back(&return_value);
    }
};
}
