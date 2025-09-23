#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetPlatformIOParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiPlatformIO&> return_value = ParameterBase<ImGuiPlatformIO&>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetPlatformIOParams() {
        params.push_back(&return_value);
    }
};
}
