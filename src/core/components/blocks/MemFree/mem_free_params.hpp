#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct MemFreeParams {
    ParameterBase<void*> ptr = ParameterBase<void*>("ptr", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    MemFreeParams() {
        params.push_back(&ptr);
    }
};
}
