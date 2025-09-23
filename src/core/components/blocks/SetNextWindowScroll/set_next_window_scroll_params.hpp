#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextWindowScrollParams {
    ParameterBase<const ImVec2&> scroll = ParameterBase<const ImVec2&>("scroll", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowScrollParams() {
        params.push_back(&scroll);
    }
};
}
