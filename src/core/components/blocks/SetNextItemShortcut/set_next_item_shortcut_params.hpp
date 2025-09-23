#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextItemShortcutParams {
    ParameterBase<ImGuiKeyChord> key_chord = ParameterBase<ImGuiKeyChord>("key_chord", ParameterType::INPUT);
    ParameterBase<ImGuiInputFlags> flags = ParameterBase<ImGuiInputFlags>("flags", ParameterType::INPUT);

    SetNextItemShortcutParams() = default;
};
