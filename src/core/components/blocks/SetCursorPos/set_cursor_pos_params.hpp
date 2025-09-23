#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetCursorPosParams : public core::IParameterParamsBase {
    ParameterBase<const ImVec2&> local_pos = ParameterBase<const ImVec2&>("local_pos", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetCursorPosParams() {
        params.push_back(&local_pos);
    }
};
}
