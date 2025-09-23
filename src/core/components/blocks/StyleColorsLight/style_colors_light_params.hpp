#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct StyleColorsLightParams {
    ParameterBase<ImGuiStyle*> dst = ParameterBase<ImGuiStyle*>("dst", ParameterType::INPUT);

    StyleColorsLightParams() = default;
};
