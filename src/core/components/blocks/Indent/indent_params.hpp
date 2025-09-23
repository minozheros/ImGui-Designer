#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct IndentParams {
    ParameterBase<float> indent_w = ParameterBase<float>("indent_w", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    IndentParams() {
        params.push_back(&indent_w);
    }
};
}
