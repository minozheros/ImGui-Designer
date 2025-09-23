#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct DebugFlashStyleColorParams {
    ParameterBase<ImGuiCol> idx = ParameterBase<ImGuiCol>("idx", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    DebugFlashStyleColorParams() {
        params.push_back(&idx);
    }
};
}
