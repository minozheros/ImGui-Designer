#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetMousePosOnOpeningCurrentPopupParams : public core::IParameterParamsBase {
    ParameterBase<ImVec2> return_value = ParameterBase<ImVec2>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetMousePosOnOpeningCurrentPopupParams() {
        params.push_back(&return_value);
    }
};
}
