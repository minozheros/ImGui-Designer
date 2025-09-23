#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextWindowContentSizeParams {
    ParameterBase<const ImVec2&> size = ParameterBase<const ImVec2&>("size", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowContentSizeParams() {
        params.push_back(&size);
    }
};
}
