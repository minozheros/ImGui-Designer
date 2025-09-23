#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct UnindentParams : public core::IParameterParamsBase {
    ParameterBase<float> indent_w = ParameterBase<float>("indent_w", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    UnindentParams() {
        params.push_back(&indent_w);
    }
};
}
