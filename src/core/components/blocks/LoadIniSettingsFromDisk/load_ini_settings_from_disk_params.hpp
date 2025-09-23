#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct LoadIniSettingsFromDiskParams {
    ParameterBase<const char*> ini_filename = ParameterBase<const char*>("ini_filename", ParameterType::INPUT);

    LoadIniSettingsFromDiskParams() = default;
};
