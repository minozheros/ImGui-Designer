#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct LoadIniSettingsFromMemoryParams : public core::IParameterParamsBase {
    ParameterBase<const char*> ini_data = ParameterBase<const char*>("ini_data", ParameterType::INPUT);
    ParameterBase<size_t> ini_size = ParameterBase<size_t>("ini_size", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    LoadIniSettingsFromMemoryParams() {
        params.push_back(&ini_data);
        params.push_back(&ini_size);
    }
};
}
