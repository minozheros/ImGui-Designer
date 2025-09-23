#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct IsKeyChordPressedParams {
    ParameterBase<ImGuiKeyChord> key_chord = ParameterBase<ImGuiKeyChord>("key_chord", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    IsKeyChordPressedParams() = default;
};
