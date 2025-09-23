#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetWindowDrawListParams : public core::IParameterParamsBase {
    ParameterBase<ImDrawList*> return_value = ParameterBase<ImDrawList*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetWindowDrawListParams() {
        params.push_back(&return_value);
    }
};
}
