#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct StyleColorsLightParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiStyle*> dst = ParameterBase<ImGuiStyle*>("dst", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    StyleColorsLightParams() {
        params.push_back(&dst);
    }
};
}
