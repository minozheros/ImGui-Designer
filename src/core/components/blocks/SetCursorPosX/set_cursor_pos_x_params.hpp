#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetCursorPosXParams : public core::IParameterParamsBase {
    ParameterBase<float> local_x = ParameterBase<float>("local_x", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetCursorPosXParams() {
        params.push_back(&local_x);
    }
};
}
