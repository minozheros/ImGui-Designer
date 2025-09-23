#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetWindowFocusParams {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);

    SetWindowFocusParams() = default;
};
