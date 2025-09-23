#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct IsRectVisibleParams : public core::IParameterParamsBase {
    ParameterBase<const ImVec2&> rect_min = ParameterBase<const ImVec2&>("rect_min", ParameterType::INPUT);
    ParameterBase<const ImVec2&> rect_max = ParameterBase<const ImVec2&>("rect_max", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    IsRectVisibleParams() {
        params.push_back(&rect_min);
        params.push_back(&rect_max);
        params.push_back(&return_value);
    }
};
}
