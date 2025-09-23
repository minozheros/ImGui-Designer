#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TreePushParams {
    ParameterBase<const void*> ptr_id = ParameterBase<const void*>("ptr_id", ParameterType::INPUT);

    TreePushParams() = default;
};
