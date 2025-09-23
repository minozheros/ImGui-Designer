#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextWindowBgAlphaParams {
    ParameterBase<float> alpha = ParameterBase<float>("alpha", ParameterType::INPUT);

    SetNextWindowBgAlphaParams() = default;
};
