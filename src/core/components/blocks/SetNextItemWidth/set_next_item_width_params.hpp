#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextItemWidthParams {
    ParameterBase<float> item_width = ParameterBase<float>("item_width", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextItemWidthParams() {
        params.push_back(&item_width);
    }
};
}
