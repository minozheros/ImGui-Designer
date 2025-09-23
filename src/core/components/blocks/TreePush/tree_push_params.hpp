#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct TreePushParams : public core::IParameterParamsBase {
    ParameterBase<const void*> ptr_id = ParameterBase<const void*>("ptr_id", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    TreePushParams() {
        params.push_back(&ptr_id);
    }
};
}
