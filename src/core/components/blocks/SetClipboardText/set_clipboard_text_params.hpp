#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetClipboardTextParams : public core::IParameterParamsBase {
    ParameterBase<const char*> text = ParameterBase<const char*>("text", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetClipboardTextParams() {
        params.push_back(&text);
    }
};
}
