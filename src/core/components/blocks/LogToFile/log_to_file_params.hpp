#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct LogToFileParams : public core::IParameterParamsBase {
    ParameterBase<int> auto_open_depth = ParameterBase<int>("auto_open_depth", ParameterType::INPUT);
    ParameterBase<const char*> filename = ParameterBase<const char*>("filename", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    LogToFileParams() {
        params.push_back(&auto_open_depth);
        params.push_back(&filename);
    }
};
}
