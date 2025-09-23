#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextItemStorageIDParams {
    ParameterBase<ImGuiID> storage_id = ParameterBase<ImGuiID>("storage_id", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextItemStorageIDParams() {
        params.push_back(&storage_id);
    }
};
}
