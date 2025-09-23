#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct MemAllocParams {
    ParameterBase<size_t> size = ParameterBase<size_t>("size", ParameterType::INPUT);
    ParameterBase<void*> return_value = ParameterBase<void*>("return_value", ParameterType::RETURN);

    MemAllocParams() = default;
};
