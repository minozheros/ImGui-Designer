#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetCursorPosYParams {
    ParameterBase<float> local_y = ParameterBase<float>("local_y", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetCursorPosYParams() {
        params.push_back(&local_y);
    }
};
}
