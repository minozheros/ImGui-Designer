#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct PushIDParams {
    ParameterBase<int> int_id = ParameterBase<int>("int_id", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushIDParams() {
        params.push_back(&int_id);
    }
};
}
