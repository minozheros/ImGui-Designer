#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct BeginDisabledParams {
    ParameterBase<bool> disabled = ParameterBase<bool>("disabled", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    BeginDisabledParams() {
        params.push_back(&disabled);
    }
};
}
