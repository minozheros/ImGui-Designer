#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct LogToFileParams {
    ParameterBase<int> auto_open_depth = ParameterBase<int>("auto_open_depth", ParameterType::INPUT);
    ParameterBase<const char*> filename = ParameterBase<const char*>("filename", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    LogToFileParams() {
        params.push_back(&auto_open_depth);
        params.push_back(&filename);
    }
};
}
