#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct StyleColorsDarkParams {
    ParameterBase<ImGuiStyle*> dst = ParameterBase<ImGuiStyle*>("dst", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    StyleColorsDarkParams() {
        params.push_back(&dst);
    }
};
}
