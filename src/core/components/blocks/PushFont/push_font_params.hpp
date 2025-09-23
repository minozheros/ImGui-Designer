#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct PushFontParams {
    ParameterBase<ImFont*> font = ParameterBase<ImFont*>("font", ParameterType::INPUT);
    ParameterBase<float> font_size_base_unscaled = ParameterBase<float>("font_size_base_unscaled", ParameterType::INPUT);

    PushFontParams() = default;
};
