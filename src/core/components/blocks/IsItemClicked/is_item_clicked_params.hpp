#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct IsItemClickedParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiMouseButton> mouse_button = ParameterBase<ImGuiMouseButton>("mouse_button", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    IsItemClickedParams() {
        params.push_back(&mouse_button);
        params.push_back(&return_value);
    }
};
}
