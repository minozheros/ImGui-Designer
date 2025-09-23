#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushItemWidthParams {
    ParameterBase<float> item_width = ParameterBase<float>("item_width", ParameterType::INPUT);

    PushItemWidthParams() = default;
};
