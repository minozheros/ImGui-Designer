#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct PushStyleVarXParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiStyleVar> idx = ParameterBase<ImGuiStyleVar>("idx", ParameterType::INPUT);
    ParameterBase<float> val_x = ParameterBase<float>("val_x", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushStyleVarXParams() {
        params.push_back(&idx);
        params.push_back(&val_x);
    }
};
}
