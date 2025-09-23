#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetStateStorageParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiStorage*> storage = ParameterBase<ImGuiStorage*>("storage", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetStateStorageParams() {
        params.push_back(&storage);
    }
};
}
