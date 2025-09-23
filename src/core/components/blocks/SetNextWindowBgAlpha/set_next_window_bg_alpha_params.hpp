#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextWindowBgAlphaParams {
    ParameterBase<float> alpha = ParameterBase<float>("alpha", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextWindowBgAlphaParams() {
        params.push_back(&alpha);
    }
};
}
