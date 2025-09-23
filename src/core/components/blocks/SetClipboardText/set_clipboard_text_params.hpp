#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetClipboardTextParams {
    ParameterBase<const char*> text = ParameterBase<const char*>("text", ParameterType::INPUT);

    SetClipboardTextParams() = default;
};
