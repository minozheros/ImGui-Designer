#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextItemShortcutParams {
    ParameterBase<ImGuiKeyChord> key_chord = ParameterBase<ImGuiKeyChord>("key_chord", ParameterType::INPUT);
    ParameterBase<ImGuiInputFlags> flags = ParameterBase<ImGuiInputFlags>("flags", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextItemShortcutParams() {
        params.push_back(&key_chord);
        params.push_back(&flags);
    }
};
}
