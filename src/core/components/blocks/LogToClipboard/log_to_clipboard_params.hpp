#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct LogToClipboardParams : public core::IParameterParamsBase {
    ParameterBase<int> auto_open_depth = ParameterBase<int>("auto_open_depth", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    LogToClipboardParams() {
        params.push_back(&auto_open_depth);
    }
};
}
