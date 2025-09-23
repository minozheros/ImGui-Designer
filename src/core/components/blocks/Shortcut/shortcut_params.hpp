#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ShortcutParams {
    ParameterBase<ImGuiKeyChord> key_chord = ParameterBase<ImGuiKeyChord>("key_chord", ParameterType::INPUT);
    ParameterBase<ImGuiInputFlags> flags = ParameterBase<ImGuiInputFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    ShortcutParams() = default;
};
