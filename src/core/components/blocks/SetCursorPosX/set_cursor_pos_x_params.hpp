#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetCursorPosXParams {
    ParameterBase<float> local_x = ParameterBase<float>("local_x", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetCursorPosXParams() {
        params.push_back(&local_x);
    }
};
}
