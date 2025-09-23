#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetColorEditOptionsParams {
    ParameterBase<ImGuiColorEditFlags> flags = ParameterBase<ImGuiColorEditFlags>("flags", ParameterType::INPUT);

    SetColorEditOptionsParams() = default;
};
