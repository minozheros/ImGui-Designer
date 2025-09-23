#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetStateStorageParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiStorage*> return_value = ParameterBase<ImGuiStorage*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetStateStorageParams() {
        params.push_back(&return_value);
    }
};
}
