#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct MemFreeParams {
    ParameterBase<void*> ptr = ParameterBase<void*>("ptr", ParameterType::INPUT);

    MemFreeParams() = default;
};
