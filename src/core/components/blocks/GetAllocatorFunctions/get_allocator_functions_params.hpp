#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetAllocatorFunctionsParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiMemAllocFunc*> p_alloc_func = ParameterBase<ImGuiMemAllocFunc*>("p_alloc_func", ParameterType::OUTPUT);
    ParameterBase<ImGuiMemFreeFunc*> p_free_func = ParameterBase<ImGuiMemFreeFunc*>("p_free_func", ParameterType::OUTPUT);
    ParameterBase<void**> p_user_data = ParameterBase<void**>("p_user_data", ParameterType::OUTPUT);

    std::vector<core::IParameterBase*> params;
    GetAllocatorFunctionsParams() {
        params.push_back(&p_alloc_func);
        params.push_back(&p_free_func);
        params.push_back(&p_user_data);
    }
};
}
