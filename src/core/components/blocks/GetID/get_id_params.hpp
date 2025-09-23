#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetIDParams : public core::IParameterParamsBase {
    ParameterBase<int> int_id = ParameterBase<int>("int_id", ParameterType::INPUT);
    ParameterBase<ImGuiID> return_value = ParameterBase<ImGuiID>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetIDParams() {
        params.push_back(&int_id);
        params.push_back(&return_value);
    }
};
}
