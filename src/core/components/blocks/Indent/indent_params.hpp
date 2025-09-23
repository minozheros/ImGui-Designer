#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct IndentParams : public core::IParameterParamsBase {
    ParameterBase<float> indent_w = ParameterBase<float>("indent_w", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    IndentParams() {
        params.push_back(&indent_w);
    }
};
}
