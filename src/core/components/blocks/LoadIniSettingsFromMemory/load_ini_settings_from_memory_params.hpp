#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct LoadIniSettingsFromMemoryParams {
    ParameterBase<const char*> ini_data = ParameterBase<const char*>("ini_data", ParameterType::INPUT);
    ParameterBase<size_t> ini_size = ParameterBase<size_t>("ini_size", ParameterType::INPUT);

    LoadIniSettingsFromMemoryParams() = default;
};
