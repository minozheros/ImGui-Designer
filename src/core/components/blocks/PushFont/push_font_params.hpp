#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct PushFontParams : public core::IParameterParamsBase {
    ParameterBase<ImFont*> font = ParameterBase<ImFont*>("font", ParameterType::INPUT);
    ParameterBase<float> font_size_base_unscaled = ParameterBase<float>("font_size_base_unscaled", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    PushFontParams() {
        params.push_back(&font);
        params.push_back(&font_size_base_unscaled);
    }
};
}
