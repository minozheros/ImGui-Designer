#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ShortcutParams {
    ParameterBase<ImGuiKeyChord> key_chord = ParameterBase<ImGuiKeyChord>("key_chord", ParameterType::INPUT);
    ParameterBase<ImGuiInputFlags> flags = ParameterBase<ImGuiInputFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    ShortcutParams() {
        params.push_back(&key_chord);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
