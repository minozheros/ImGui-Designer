#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ShowStyleEditorParams {
    ParameterBase<ImGuiStyle*> ref = ParameterBase<ImGuiStyle*>("ref", ParameterType::INPUT);

    ShowStyleEditorParams() = default;
};
