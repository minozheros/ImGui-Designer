#pragma once
#include <imgui.h>

struct SetAllocatorFunctionsParams {
    ImGuiMemAllocFunc alloc_func;
    ImGuiMemFreeFunc free_func;
    void* user_data;
};
