#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct PopStyleColorParams : public core::IParameterParamsBase {
    ParameterBase<int> count = ParameterBase<int>("count", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PopStyleColorParams() {
        params.push_back(&count);
    }
};
}
