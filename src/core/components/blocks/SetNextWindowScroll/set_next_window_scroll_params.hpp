#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetNextWindowScrollParams : public core::IParameterParamsBase {
    ParameterBase<const ImVec2&> scroll = ParameterBase<const ImVec2&>("scroll", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowScrollParams() {
        params.push_back(&scroll);
    }
};
}
