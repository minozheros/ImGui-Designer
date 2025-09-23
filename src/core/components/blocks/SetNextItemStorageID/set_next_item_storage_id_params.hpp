#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetNextItemStorageIDParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiID> storage_id = ParameterBase<ImGuiID>("storage_id", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextItemStorageIDParams() {
        params.push_back(&storage_id);
    }
};
}
