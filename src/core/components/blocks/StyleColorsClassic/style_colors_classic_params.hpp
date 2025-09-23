#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct StyleColorsClassicParams {
    ParameterBase<ImGuiStyle*> dst = ParameterBase<ImGuiStyle*>("dst", ParameterType::INPUT);

    StyleColorsClassicParams() = default;
};
