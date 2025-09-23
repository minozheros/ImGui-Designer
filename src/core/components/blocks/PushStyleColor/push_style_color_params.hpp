#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct PushStyleColorParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiCol> idx = ParameterBase<ImGuiCol>("idx", ParameterType::INPUT);
    ParameterBase<const ImVec4&> col = ParameterBase<const ImVec4&>("col", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushStyleColorParams() {
        params.push_back(&idx);
        params.push_back(&col);
    }
};
}
