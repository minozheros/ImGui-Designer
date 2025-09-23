#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetStateStorageParams {
    ParameterBase<ImGuiStorage*> storage = ParameterBase<ImGuiStorage*>("storage", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetStateStorageParams() {
        params.push_back(&storage);
    }
};
}
