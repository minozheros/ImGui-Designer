#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct LogToClipboardParams {
    ParameterBase<int> auto_open_depth = ParameterBase<int>("auto_open_depth", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    LogToClipboardParams() {
        params.push_back(&auto_open_depth);
    }
};
}
