#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextItemWidthParams {
    ParameterBase<float> item_width = ParameterBase<float>("item_width", ParameterType::INPUT);

    SetNextItemWidthParams() = default;
};
