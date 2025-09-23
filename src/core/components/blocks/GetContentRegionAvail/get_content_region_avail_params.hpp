#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetContentRegionAvailParams {
    ParameterBase<ImVec2> return_value = ParameterBase<ImVec2>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetContentRegionAvailParams() {
        params.push_back(&return_value);
    }
};
}
