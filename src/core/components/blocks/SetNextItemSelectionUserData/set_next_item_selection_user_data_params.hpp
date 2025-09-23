#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetNextItemSelectionUserDataParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiSelectionUserData> selection_user_data = ParameterBase<ImGuiSelectionUserData>("selection_user_data", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextItemSelectionUserDataParams() {
        params.push_back(&selection_user_data);
    }
};
}
