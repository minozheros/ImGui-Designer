#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetMouseCursorParams : public core::IParameterParamsBase {
    ParameterBase<ImGuiMouseCursor> cursor_type = ParameterBase<ImGuiMouseCursor>("cursor_type", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetMouseCursorParams() {
        params.push_back(&cursor_type);
    }
};
}
