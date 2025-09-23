#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct PushItemWidthParams : public core::IParameterParamsBase {
    ParameterBase<float> item_width = ParameterBase<float>("item_width", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushItemWidthParams() {
        params.push_back(&item_width);
    }
};
}
