#pragma once
#include <imgui.h>

struct GetAllocatorFunctionsParams {
    ImGuiMemAllocFunc* p_alloc_func;
    ImGuiMemFreeFunc* p_free_func;
    void** p_user_data;
};
