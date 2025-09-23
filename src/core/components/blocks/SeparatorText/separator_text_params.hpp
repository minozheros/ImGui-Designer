#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SeparatorTextParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SeparatorTextParams() {
        params.push_back(&label);
    }
};
}
