#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct DebugFlashStyleColorParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiCol> idx = ParameterBase<ImGuiCol>("idx", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    DebugFlashStyleColorParams() {
        params.push_back(&idx);
    }
};
}
