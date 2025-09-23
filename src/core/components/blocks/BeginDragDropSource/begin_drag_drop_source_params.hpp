#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct BeginDragDropSourceParams {
    ParameterBase<ImGuiDragDropFlags> flags = ParameterBase<ImGuiDragDropFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    BeginDragDropSourceParams() = default;
};
