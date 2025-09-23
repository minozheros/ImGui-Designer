#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct PushIDParams : public core::IParameterParamsBase {
    ParameterBase<int> int_id = ParameterBase<int>("int_id", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushIDParams() {
        params.push_back(&int_id);
    }
};
}
