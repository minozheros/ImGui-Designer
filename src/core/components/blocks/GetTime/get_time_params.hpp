#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetTimeParams : public core::IParameterParamsBase {
    ParameterBase<double> return_value = ParameterBase<double>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetTimeParams() {
        params.push_back(&return_value);
    }
};
}
