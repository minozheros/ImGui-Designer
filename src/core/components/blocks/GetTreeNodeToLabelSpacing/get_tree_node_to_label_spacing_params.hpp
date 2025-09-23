#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetTreeNodeToLabelSpacingParams : public core::IParameterParamsBase {
    ParameterBase<float> return_value = ParameterBase<float>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetTreeNodeToLabelSpacingParams() {
        params.push_back(&return_value);
    }
};
}
