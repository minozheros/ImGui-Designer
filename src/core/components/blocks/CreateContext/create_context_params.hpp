#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct CreateContextParams : public core::IParameterParamsBase {
    ParameterBase<ImFontAtlas*> shared_font_atlas = ParameterBase<ImFontAtlas*>("shared_font_atlas", ParameterType::INPUT);
    ParameterBase<ImGuiContext*> return_value = ParameterBase<ImGuiContext*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    CreateContextParams() {
        params.push_back(&shared_font_atlas);
        params.push_back(&return_value);
    }
};
}
