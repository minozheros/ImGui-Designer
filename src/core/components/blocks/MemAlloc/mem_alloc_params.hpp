#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct MemAllocParams {
    ParameterBase<size_t> size = ParameterBase<size_t>("size", ParameterType::INPUT);
    ParameterBase<void*> return_value = ParameterBase<void*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    MemAllocParams() {
        params.push_back(&size);
        params.push_back(&return_value);
    }
};
}
