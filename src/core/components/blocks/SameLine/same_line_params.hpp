#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SameLineParams {
    ParameterBase<float> offset_from_start_x = ParameterBase<float>("offset_from_start_x", ParameterType::INPUT);
    ParameterBase<float> spacing = ParameterBase<float>("spacing", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SameLineParams() {
        params.push_back(&offset_from_start_x);
        params.push_back(&spacing);
    }
};
}
