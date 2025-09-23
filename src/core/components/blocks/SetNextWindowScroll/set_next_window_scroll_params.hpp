#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextWindowScrollParams {
    ParameterBase<const ImVec2&> scroll = ParameterBase<const ImVec2&>("scroll", ParameterType::INPUT);

    SetNextWindowScrollParams() = default;
};
