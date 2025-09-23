#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetKeyboardFocusHereParams {
    ParameterBase<int> offset = ParameterBase<int>("offset", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetKeyboardFocusHereParams() {
        params.push_back(&offset);
    }
};
}
