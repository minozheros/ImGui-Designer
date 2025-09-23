#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct ShowStyleEditorParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiStyle*> ref = ParameterBase<ImGuiStyle*>("ref", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    ShowStyleEditorParams() {
        params.push_back(&ref);
    }
};
}
