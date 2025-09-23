#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetDragDropPayloadParams {
    ParameterBase<const char*> type = ParameterBase<const char*>("type", ParameterType::INPUT);
    ParameterBase<const void*> data = ParameterBase<const void*>("data", ParameterType::INPUT);
    ParameterBase<size_t> sz = ParameterBase<size_t>("sz", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    SetDragDropPayloadParams() = default;
};
