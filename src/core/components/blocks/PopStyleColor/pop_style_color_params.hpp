#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct PopStyleColorParams {
    ParameterBase<int> count = ParameterBase<int>("count", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PopStyleColorParams() {
        params.push_back(&count);
    }
};
}
