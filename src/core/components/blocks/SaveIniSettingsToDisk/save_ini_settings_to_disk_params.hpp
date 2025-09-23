#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SaveIniSettingsToDiskParams {
    ParameterBase<const char*> ini_filename = ParameterBase<const char*>("ini_filename", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SaveIniSettingsToDiskParams() {
        params.push_back(&ini_filename);
    }
};
}
