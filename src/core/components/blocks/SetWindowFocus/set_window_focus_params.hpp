#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetWindowFocusParams : public core::IParameterParamsBase {
    ParameterBase<const char*> name = ParameterBase<const char*>("name", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetWindowFocusParams() {
        params.push_back(&name);
    }
};
}
