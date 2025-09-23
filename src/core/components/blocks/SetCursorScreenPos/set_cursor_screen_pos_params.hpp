#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetCursorScreenPosParams {
    ParameterBase<const ImVec2&> pos = ParameterBase<const ImVec2&>("pos", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetCursorScreenPosParams() {
        params.push_back(&pos);
    }
};
}
