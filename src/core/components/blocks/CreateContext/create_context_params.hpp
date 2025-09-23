#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct CreateContextParams {
    ParameterBase<ImFontAtlas*> shared_font_atlas = ParameterBase<ImFontAtlas*>("shared_font_atlas", ParameterType::INPUT);
    ParameterBase<ImGuiContext*> return_value = ParameterBase<ImGuiContext*>("return_value", ParameterType::RETURN);

    CreateContextParams() = default;
};
