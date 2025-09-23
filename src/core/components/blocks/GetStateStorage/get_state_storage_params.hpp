#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetStateStorageParams {
    ParameterBase<ImGuiStorage*> return_value = ParameterBase<ImGuiStorage*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetStateStorageParams() {
        params.push_back(&return_value);
    }
};
}
