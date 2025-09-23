#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ShowStyleEditorParams {
    ParameterBase<ImGuiStyle*> ref = ParameterBase<ImGuiStyle*>("ref", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    ShowStyleEditorParams() {
        params.push_back(&ref);
    }
};
}
