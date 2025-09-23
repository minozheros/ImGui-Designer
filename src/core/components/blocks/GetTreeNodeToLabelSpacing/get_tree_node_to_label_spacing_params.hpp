#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetTreeNodeToLabelSpacingParams {
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetTreeNodeToLabelSpacingParams() {
        params.push_back(&return_value);
    }
};
}
