#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetCursorScreenPosParams : public core::IParameterParamsBase {
    ParameterBase<const ImVec2&> pos = ParameterBase<const ImVec2&>("pos", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetCursorScreenPosParams() {
        params.push_back(&pos);
    }
};
}
