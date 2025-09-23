#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetIOParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiIO&> return_value = ParameterBase<ImGuiIO&>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetIOParams() {
        params.push_back(&return_value);
    }
};
}
