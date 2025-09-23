#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetAllocatorFunctionsParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiMemAllocFunc> alloc_func = ParameterBase<ImGuiMemAllocFunc>("alloc_func", ParameterType::INPUT);
    ParameterBase<ImGuiMemFreeFunc> free_func = ParameterBase<ImGuiMemFreeFunc>("free_func", ParameterType::INPUT);
    ParameterBase<void*> user_data = ParameterBase<void*>("user_data", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetAllocatorFunctionsParams() {
        params.push_back(&alloc_func);
        params.push_back(&free_func);
        params.push_back(&user_data);
    }
};
}
