#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct PushStyleVarParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiStyleVar> idx = ParameterBase<ImGuiStyleVar>("idx", ParameterType::INPUT);
    ParameterBase<const ImVec2&> val = ParameterBase<const ImVec2&>("val", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushStyleVarParams() {
        params.push_back(&idx);
        params.push_back(&val);
    }
};
}
