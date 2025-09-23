#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct IsWindowHoveredParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiHoveredFlags> flags = ParameterBase<ImGuiHoveredFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    IsWindowHoveredParams() {
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
