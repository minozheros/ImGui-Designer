#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct OpenPopupOnItemClickParams {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<ImGuiPopupFlags> popup_flags = ParameterBase<ImGuiPopupFlags>("popup_flags", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    OpenPopupOnItemClickParams() {
        params.push_back(&str_id);
        params.push_back(&popup_flags);
    }
};
}
