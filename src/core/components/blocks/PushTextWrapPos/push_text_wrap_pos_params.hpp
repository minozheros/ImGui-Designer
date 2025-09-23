#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct PushTextWrapPosParams {
    ParameterBase<float> wrap_local_pos_x = ParameterBase<float>("wrap_local_pos_x", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushTextWrapPosParams() {
        params.push_back(&wrap_local_pos_x);
    }
};
}
