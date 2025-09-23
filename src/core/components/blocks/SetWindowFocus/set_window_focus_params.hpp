#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetWindowFocusParams {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetWindowFocusParams() {
        params.push_back(&name);
    }
};
}
