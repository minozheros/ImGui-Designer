#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct ShowDemoWindowParams {
    ParameterBase<bool*> p_open = ParameterBase<bool*>("p_open", ParameterType::OUTPUT);

    ShowDemoWindowParams() = default;
};
