#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct CheckboxFlagsParams : public core::IParameterParamsBase {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<unsigned int*> flags = ParameterBase<unsigned int*>("flags", ParameterType::INPUT);
    ParameterBase<unsigned int> flags_value = ParameterBase<unsigned int>("flags_value", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    CheckboxFlagsParams() {
        params.push_back(&label);
        params.push_back(&flags);
        params.push_back(&flags_value);
        params.push_back(&return_value);
    }
};
}
