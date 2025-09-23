#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetColorEditOptionsParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiColorEditFlags> flags = ParameterBase<ImGuiColorEditFlags>("flags", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetColorEditOptionsParams() {
        params.push_back(&flags);
    }
};
}
