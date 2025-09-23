#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetColorEditOptionsParams {
    ParameterBase<ImGuiColorEditFlags> flags = ParameterBase<ImGuiColorEditFlags>("flags", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetColorEditOptionsParams() {
        params.push_back(&flags);
    }
};
}
