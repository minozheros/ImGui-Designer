#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct UnindentParams {
    ParameterBase<float> indent_w = ParameterBase<float>("indent_w", ParameterType::INPUT);

    UnindentParams() = default;
};
