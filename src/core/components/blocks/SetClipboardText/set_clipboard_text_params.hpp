#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetClipboardTextParams {
    ParameterBase<const char*> text = ParameterBase<const char*>("text", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetClipboardTextParams() {
        params.push_back(&text);
    }
};
}
