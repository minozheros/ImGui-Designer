#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ShowDebugLogWindowParams {
    ParameterBase<bool*> p_open = ParameterBase<bool*>("p_open", ParameterType::OUTPUT);

    ShowDebugLogWindowParams() = default;
};
