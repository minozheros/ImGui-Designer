#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetDrawDataParams : public core::IParameterParamsBase {
    ParameterBase<ImDrawData*> return_value = ParameterBase<ImDrawData*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetDrawDataParams() {
        params.push_back(&return_value);
    }
};
}
