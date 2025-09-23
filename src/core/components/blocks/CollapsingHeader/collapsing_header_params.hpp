#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct CollapsingHeaderParams : public core::IParameterParamsBase {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<bool*> p_visible = ParameterBase<bool*>("p_visible", ParameterType::OUTPUT);
    ParameterBase<ImGuiTreeNodeFlags> flags = ParameterBase<ImGuiTreeNodeFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    CollapsingHeaderParams() {
        params.push_back(&label);
        params.push_back(&p_visible);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
