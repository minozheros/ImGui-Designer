#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetAllocatorFunctionsParams {
    ParameterBase<ImGuiMemAllocFunc> alloc_func = ParameterBase<ImGuiMemAllocFunc>("alloc_func", ParameterType::INPUT);
    ParameterBase<ImGuiMemFreeFunc> free_func = ParameterBase<ImGuiMemFreeFunc>("free_func", ParameterType::INPUT);
    ParameterBase<void*> user_data = ParameterBase<void*>("user_data", ParameterType::INPUT);

    SetAllocatorFunctionsParams() = default;
};
