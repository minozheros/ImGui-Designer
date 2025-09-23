#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct PopStyleVarParams : public core::IParameterParamsBase {
    ParameterBase<int> count = ParameterBase<int>("count", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PopStyleVarParams() {
        params.push_back(&count);
    }
};
}
