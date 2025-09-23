#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct GetAllocatorFunctionsParams {
    ParameterBase<ImGuiMemAllocFunc*> p_alloc_func = ParameterBase<ImGuiMemAllocFunc*>("p_alloc_func", ParameterType::OUTPUT);
    ParameterBase<ImGuiMemFreeFunc*> p_free_func = ParameterBase<ImGuiMemFreeFunc*>("p_free_func", ParameterType::OUTPUT);
    ParameterBase<void**> p_user_data = ParameterBase<void**>("p_user_data", ParameterType::OUTPUT);

    GetAllocatorFunctionsParams() = default;
};
