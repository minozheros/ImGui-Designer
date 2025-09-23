#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetNavCursorVisibleParams : public core::IParameterParamsBase {
    ParameterBase<bool> visible = ParameterBase<bool>("visible", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNavCursorVisibleParams() {
        params.push_back(&visible);
    }
};
}
