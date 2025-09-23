#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetDrawListSharedDataParams {
    ParameterBase<ImDrawListSharedData*> return_value = ParameterBase<ImDrawListSharedData*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetDrawListSharedDataParams() {
        params.push_back(&return_value);
    }
};
}
