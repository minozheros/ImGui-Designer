#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetMouseCursorParams {
    ParameterBase<ImGuiMouseCursor> cursor_type = ParameterBase<ImGuiMouseCursor>("cursor_type", ParameterType::INPUT);

    SetMouseCursorParams() = default;
};
