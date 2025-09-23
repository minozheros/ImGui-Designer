#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct BeginPopupParams : public core::IParameterParamsBase {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<ImGuiWindowFlags> flags = ParameterBase<ImGuiWindowFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    BeginPopupParams() {
        params.push_back(&str_id);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
