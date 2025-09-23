#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetMouseCursorParams {
    ParameterBase<ImGuiMouseCursor> return_value = ParameterBase<ImGuiMouseCursor>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetMouseCursorParams() {
        params.push_back(&return_value);
    }
};
}
