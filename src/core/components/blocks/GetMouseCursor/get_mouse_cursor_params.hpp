#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetMouseCursorParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiMouseCursor> return_value = ParameterBase<ImGuiMouseCursor>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetMouseCursorParams() {
        params.push_back(&return_value);
    }
};
}
