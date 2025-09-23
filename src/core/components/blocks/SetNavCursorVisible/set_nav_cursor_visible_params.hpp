#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNavCursorVisibleParams {
    ParameterBase<bool> visible = ParameterBase<bool>("visible", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNavCursorVisibleParams() {
        params.push_back(&visible);
    }
};
}
