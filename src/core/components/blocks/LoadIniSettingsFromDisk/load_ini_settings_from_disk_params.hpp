#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct LoadIniSettingsFromDiskParams {
    ParameterBase<const char*> ini_filename = ParameterBase<const char*>("ini_filename", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    LoadIniSettingsFromDiskParams() {
        params.push_back(&ini_filename);
    }
};
}
