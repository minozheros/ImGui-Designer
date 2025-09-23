#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetStyleParams {
    ParameterBase<ImGuiStyle&> return_value = ParameterBase<ImGuiStyle&>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetStyleParams() {
        params.push_back(&return_value);
    }
};
}
