#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct OpenPopupParams {
    ParameterBase<ImGuiID> id = ParameterBase<ImGuiID>("id", ParameterType::INPUT);
    ParameterBase<ImGuiPopupFlags> popup_flags = ParameterBase<ImGuiPopupFlags>("popup_flags", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    OpenPopupParams() {
        params.push_back(&id);
        params.push_back(&popup_flags);
    }
};
}
