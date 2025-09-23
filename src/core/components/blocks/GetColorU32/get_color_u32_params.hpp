#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetColorU32Params : public core::IParameterParamsBase {
    ParameterBase<ImU32> col = ParameterBase<ImU32>("col", ParameterType::INPUT);
    ParameterBase<float> alpha_mul = ParameterBase<float>("alpha_mul", ParameterType::INPUT);
    ParameterBase<ImU32> return_value = ParameterBase<ImU32>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetColorU32Params() {
        params.push_back(&col);
        params.push_back(&alpha_mul);
        params.push_back(&return_value);
    }
};
}
