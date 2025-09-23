#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetMouseCursorParams {
    ParameterBase<ImGuiMouseCursor> return_value = ParameterBase<ImGuiMouseCursor>("return_value", ParameterType::RETURN);

    GetMouseCursorParams() = default;
};
