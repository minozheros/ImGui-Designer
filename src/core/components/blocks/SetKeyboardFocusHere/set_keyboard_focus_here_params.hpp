#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetKeyboardFocusHereParams : public core::IParameterParamsBase {
    ParameterBase<int> offset = ParameterBase<int>("offset", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetKeyboardFocusHereParams() {
        params.push_back(&offset);
    }
};
}
