#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TreePushParams {
    ParameterBase<const void*> ptr_id = ParameterBase<const void*>("ptr_id", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    TreePushParams() {
        params.push_back(&ptr_id);
    }
};
}
