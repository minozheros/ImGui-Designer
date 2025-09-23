#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct LogToTTYParams {
    ParameterBase<int> auto_open_depth = ParameterBase<int>("auto_open_depth", ParameterType::INPUT);

    LogToTTYParams() = default;
};
