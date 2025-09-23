#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetStyleParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiStyle&> return_value = ParameterBase<ImGuiStyle&>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetStyleParams() {
        params.push_back(&return_value);
    }
};
}
