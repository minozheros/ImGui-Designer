#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct LogToFileParams {
    ParameterBase<int> auto_open_depth = ParameterBase<int>("auto_open_depth", ParameterType::INPUT);
    ParameterBase<const char*> filename = ParameterBase<const char*>("filename", ParameterType::INPUT);

    LogToFileParams() = default;
};
